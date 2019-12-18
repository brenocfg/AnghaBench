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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AMOPOPID ; 
 int /*<<< orphan*/  CacheRegisterRelcacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CacheRegisterSyscacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FOREIGNDATAWRAPPEROID ; 
 int /*<<< orphan*/  FOREIGNSERVEROID ; 
 int /*<<< orphan*/  NAMESPACEOID ; 
 int /*<<< orphan*/  OPEROID ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  PlanCacheObjectCallback ; 
 int /*<<< orphan*/  PlanCacheRelCallback ; 
 int /*<<< orphan*/  PlanCacheSysCallback ; 
 int /*<<< orphan*/  TYPEOID ; 

void
InitPlanCache(void)
{
	CacheRegisterRelcacheCallback(PlanCacheRelCallback, (Datum) 0);
	CacheRegisterSyscacheCallback(PROCOID, PlanCacheObjectCallback, (Datum) 0);
	CacheRegisterSyscacheCallback(TYPEOID, PlanCacheObjectCallback, (Datum) 0);
	CacheRegisterSyscacheCallback(NAMESPACEOID, PlanCacheSysCallback, (Datum) 0);
	CacheRegisterSyscacheCallback(OPEROID, PlanCacheSysCallback, (Datum) 0);
	CacheRegisterSyscacheCallback(AMOPOPID, PlanCacheSysCallback, (Datum) 0);
	CacheRegisterSyscacheCallback(FOREIGNSERVEROID, PlanCacheSysCallback, (Datum) 0);
	CacheRegisterSyscacheCallback(FOREIGNDATAWRAPPEROID, PlanCacheSysCallback, (Datum) 0);
}