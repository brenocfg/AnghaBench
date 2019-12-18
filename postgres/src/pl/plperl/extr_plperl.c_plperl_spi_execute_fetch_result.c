#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  UV ;
struct TYPE_4__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ * vals; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  TYPE_1__ SPITupleTable ;
typedef  int /*<<< orphan*/  NV ;
typedef  int /*<<< orphan*/  HV ;
typedef  int /*<<< orphan*/  AV ;

/* Variables and functions */
 scalar_t__ AV_SIZE_MAX ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SPI_freetuptable (TYPE_1__*) ; 
 int /*<<< orphan*/  SPI_result_code_string (int) ; 
 scalar_t__ UV_MAX ; 
 int /*<<< orphan*/  av_extend (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  av_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_spi_usage_allowed () ; 
 int /*<<< orphan*/  cstr2sv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  hv_store_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newAV () ; 
 int /*<<< orphan*/ * newHV () ; 
 int /*<<< orphan*/  newRV_noinc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newSVnv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newSVuv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * plperl_hash_from_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HV  *
plperl_spi_execute_fetch_result(SPITupleTable *tuptable, uint64 processed,
								int status)
{
	dTHX;
	HV		   *result;

	check_spi_usage_allowed();

	result = newHV();

	hv_store_string(result, "status",
					cstr2sv(SPI_result_code_string(status)));
	hv_store_string(result, "processed",
					(processed > (uint64) UV_MAX) ?
					newSVnv((NV) processed) :
					newSVuv((UV) processed));

	if (status > 0 && tuptable)
	{
		AV		   *rows;
		SV		   *row;
		uint64		i;

		/* Prevent overflow in call to av_extend() */
		if (processed > (uint64) AV_SIZE_MAX)
			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("query result has too many rows to fit in a Perl array")));

		rows = newAV();
		av_extend(rows, processed);
		for (i = 0; i < processed; i++)
		{
			row = plperl_hash_from_tuple(tuptable->vals[i], tuptable->tupdesc, true);
			av_push(rows, row);
		}
		hv_store_string(result, "rows",
						newRV_noinc((SV *) rows));
	}

	SPI_freetuptable(tuptable);

	return result;
}