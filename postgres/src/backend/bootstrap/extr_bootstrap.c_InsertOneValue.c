#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_4__ {int /*<<< orphan*/  atttypid; } ;
struct TYPE_3__ {int /*<<< orphan*/  rd_att; } ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int) ; 
 int /*<<< orphan*/  DEBUG4 ; 
 int MAXATTR ; 
 int /*<<< orphan*/  OidInputFunctionCall (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  boot_get_type_io_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* boot_reldesc ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * values ; 

void
InsertOneValue(char *value, int i)
{
	Oid			typoid;
	int16		typlen;
	bool		typbyval;
	char		typalign;
	char		typdelim;
	Oid			typioparam;
	Oid			typinput;
	Oid			typoutput;

	AssertArg(i >= 0 && i < MAXATTR);

	elog(DEBUG4, "inserting column %d value \"%s\"", i, value);

	typoid = TupleDescAttr(boot_reldesc->rd_att, i)->atttypid;

	boot_get_type_io_data(typoid,
						  &typlen, &typbyval, &typalign,
						  &typdelim, &typioparam,
						  &typinput, &typoutput);

	values[i] = OidInputFunctionCall(typinput, value, typioparam, -1);

	/*
	 * We use ereport not elog here so that parameters aren't evaluated unless
	 * the message is going to be printed, which generally it isn't
	 */
	ereport(DEBUG4,
			(errmsg_internal("inserted -> %s",
							 OidOutputFunctionCall(typoutput, values[i]))));
}