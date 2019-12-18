#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int Size ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetDatum (unsigned char*) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FindDefaultConversionProc (int,int) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  IsTransactionState () ; 
 int MAX_CONVERSION_GROWTH ; 
 int MaxAllocHugeSize ; 
 int MaxAllocSize ; 
 scalar_t__ MemoryContextAllocHuge (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OidFunctionCall5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int PG_SQL_ASCII ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  pg_encoding_to_char (int) ; 
 int /*<<< orphan*/  pg_verify_mbstr (int,char const*,int,int) ; 
 scalar_t__ repalloc (unsigned char*,int) ; 
 int strlen (char*) ; 

unsigned char *
pg_do_encoding_conversion(unsigned char *src, int len,
						  int src_encoding, int dest_encoding)
{
	unsigned char *result;
	Oid			proc;

	if (len <= 0)
		return src;				/* empty string is always valid */

	if (src_encoding == dest_encoding)
		return src;				/* no conversion required, assume valid */

	if (dest_encoding == PG_SQL_ASCII)
		return src;				/* any string is valid in SQL_ASCII */

	if (src_encoding == PG_SQL_ASCII)
	{
		/* No conversion is possible, but we must validate the result */
		(void) pg_verify_mbstr(dest_encoding, (const char *) src, len, false);
		return src;
	}

	if (!IsTransactionState())	/* shouldn't happen */
		elog(ERROR, "cannot perform encoding conversion outside a transaction");

	proc = FindDefaultConversionProc(src_encoding, dest_encoding);
	if (!OidIsValid(proc))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("default conversion function for encoding \"%s\" to \"%s\" does not exist",
						pg_encoding_to_char(src_encoding),
						pg_encoding_to_char(dest_encoding))));

	/*
	 * Allocate space for conversion result, being wary of integer overflow.
	 *
	 * len * MAX_CONVERSION_GROWTH is typically a vast overestimate of the
	 * required space, so it might exceed MaxAllocSize even though the result
	 * would actually fit.  We do not want to hand back a result string that
	 * exceeds MaxAllocSize, because callers might not cope gracefully --- but
	 * if we just allocate more than that, and don't use it, that's fine.
	 */
	if ((Size) len >= (MaxAllocHugeSize / (Size) MAX_CONVERSION_GROWTH))
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("out of memory"),
				 errdetail("String of %d bytes is too long for encoding conversion.",
						   len)));

	result = (unsigned char *)
		MemoryContextAllocHuge(CurrentMemoryContext,
							   (Size) len * MAX_CONVERSION_GROWTH + 1);

	OidFunctionCall5(proc,
					 Int32GetDatum(src_encoding),
					 Int32GetDatum(dest_encoding),
					 CStringGetDatum(src),
					 CStringGetDatum(result),
					 Int32GetDatum(len));

	/*
	 * If the result is large, it's worth repalloc'ing to release any extra
	 * space we asked for.  The cutoff here is somewhat arbitrary, but we
	 * *must* check when len * MAX_CONVERSION_GROWTH exceeds MaxAllocSize.
	 */
	if (len > 1000000)
	{
		Size		resultlen = strlen((char *) result);

		if (resultlen >= MaxAllocSize)
			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("out of memory"),
					 errdetail("String of %d bytes is too long for encoding conversion.",
							   len)));

		result = (unsigned char *) repalloc(result, resultlen + 1);
	}

	return result;
}