#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dno; } ;
typedef  TYPE_1__ PLpgSQL_datum ;

/* Variables and functions */
 int datums_alloc ; 
 TYPE_1__** plpgsql_Datums ; 
 int plpgsql_nDatums ; 
 TYPE_1__** repalloc (TYPE_1__**,int) ; 

void
plpgsql_adddatum(PLpgSQL_datum *newdatum)
{
	if (plpgsql_nDatums == datums_alloc)
	{
		datums_alloc *= 2;
		plpgsql_Datums = repalloc(plpgsql_Datums, sizeof(PLpgSQL_datum *) * datums_alloc);
	}

	newdatum->dno = plpgsql_nDatums;
	plpgsql_Datums[plpgsql_nDatums++] = newdatum;
}