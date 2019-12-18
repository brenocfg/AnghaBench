#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_10__ {int attnum; } ;
struct TYPE_9__ {int /*<<< orphan*/  attisdropped; int /*<<< orphan*/  attname; } ;
struct TYPE_8__ {int natts; } ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  TYPE_3__ FormData_pg_attribute ;

/* Variables and functions */
 int SPI_ERROR_NOATTRIBUTE ; 
 TYPE_3__* SystemAttributeByName (char const*) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 scalar_t__ namestrcmp (int /*<<< orphan*/ *,char const*) ; 

int
SPI_fnumber(TupleDesc tupdesc, const char *fname)
{
	int			res;
	const FormData_pg_attribute *sysatt;

	for (res = 0; res < tupdesc->natts; res++)
	{
		Form_pg_attribute attr = TupleDescAttr(tupdesc, res);

		if (namestrcmp(&attr->attname, fname) == 0 &&
			!attr->attisdropped)
			return res + 1;
	}

	sysatt = SystemAttributeByName(fname);
	if (sysatt != NULL)
		return sysatt->attnum;

	/* SPI_ERROR_NOATTRIBUTE is different from all sys column numbers */
	return SPI_ERROR_NOATTRIBUTE;
}