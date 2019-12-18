#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_9__ {char* data; int len; int cursor; } ;
struct TYPE_8__ {TYPE_2__ attribute_buf; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__* CopyState ;

/* Variables and functions */
 int CopyGetData (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  CopyGetInt32 (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  ERRCODE_BAD_COPY_FILE_FORMAT ; 
 int /*<<< orphan*/  ERRCODE_INVALID_BINARY_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ReceiveFunctionCall (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enlargeStringInfo (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_2__*) ; 

__attribute__((used)) static Datum
CopyReadBinaryAttribute(CopyState cstate,
						int column_no, FmgrInfo *flinfo,
						Oid typioparam, int32 typmod,
						bool *isnull)
{
	int32		fld_size;
	Datum		result;

	if (!CopyGetInt32(cstate, &fld_size))
		ereport(ERROR,
				(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
				 errmsg("unexpected EOF in COPY data")));
	if (fld_size == -1)
	{
		*isnull = true;
		return ReceiveFunctionCall(flinfo, NULL, typioparam, typmod);
	}
	if (fld_size < 0)
		ereport(ERROR,
				(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
				 errmsg("invalid field size")));

	/* reset attribute_buf to empty, and load raw data in it */
	resetStringInfo(&cstate->attribute_buf);

	enlargeStringInfo(&cstate->attribute_buf, fld_size);
	if (CopyGetData(cstate, cstate->attribute_buf.data,
					fld_size, fld_size) != fld_size)
		ereport(ERROR,
				(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
				 errmsg("unexpected EOF in COPY data")));

	cstate->attribute_buf.len = fld_size;
	cstate->attribute_buf.data[fld_size] = '\0';

	/* Call the column type's binary input converter */
	result = ReceiveFunctionCall(flinfo, &cstate->attribute_buf,
								 typioparam, typmod);

	/* Trouble if it didn't eat the whole buffer */
	if (cstate->attribute_buf.cursor != cstate->attribute_buf.len)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_BINARY_REPRESENTATION),
				 errmsg("incorrect binary data format")));

	*isnull = false;
	return result;
}