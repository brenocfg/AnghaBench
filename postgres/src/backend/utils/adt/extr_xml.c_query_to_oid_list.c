#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64 ;
struct TYPE_2__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ * vals; } ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetObjectId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
 int SPI_OK_SELECT ; 
 int SPI_execute (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_getbinval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 size_t SPI_processed ; 
 int /*<<< orphan*/  SPI_result_code_string (int) ; 
 TYPE_1__* SPI_tuptable ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
query_to_oid_list(const char *query)
{
	uint64		i;
	List	   *list = NIL;
	int			spi_result;

	spi_result = SPI_execute(query, true, 0);
	if (spi_result != SPI_OK_SELECT)
		elog(ERROR, "SPI_execute returned %s for %s",
			 SPI_result_code_string(spi_result), query);

	for (i = 0; i < SPI_processed; i++)
	{
		Datum		oid;
		bool		isnull;

		oid = SPI_getbinval(SPI_tuptable->vals[i],
							SPI_tuptable->tupdesc,
							1,
							&isnull);
		if (!isnull)
			list = lappend_oid(list, DatumGetObjectId(oid));
	}

	return list;
}