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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AMOPOPID ; 
 int /*<<< orphan*/  AMOP_SEARCH ; 
 int /*<<< orphan*/  CharGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int SearchSysCacheExists3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
op_in_opfamily(Oid opno, Oid opfamily)
{
	return SearchSysCacheExists3(AMOPOPID,
								 ObjectIdGetDatum(opno),
								 CharGetDatum(AMOP_SEARCH),
								 ObjectIdGetDatum(opfamily));
}