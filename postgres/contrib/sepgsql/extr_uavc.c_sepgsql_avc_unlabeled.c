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
typedef  int /*<<< orphan*/  security_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 char* MemoryContextStrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_FINALLY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  avc_mem_cxt ; 
 char* avc_unlabeled ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  freecon (int /*<<< orphan*/ ) ; 
 scalar_t__ security_get_initial_context_raw (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
sepgsql_avc_unlabeled(void)
{
	if (!avc_unlabeled)
	{
		security_context_t unlabeled;

		if (security_get_initial_context_raw("unlabeled", &unlabeled) < 0)
			ereport(ERROR,
					(errcode(ERRCODE_INTERNAL_ERROR),
					 errmsg("SELinux: failed to get initial security label: %m")));
		PG_TRY();
		{
			avc_unlabeled = MemoryContextStrdup(avc_mem_cxt, unlabeled);
		}
		PG_FINALLY();
		{
			freecon(unlabeled);
		}
		PG_END_TRY();
	}
	return avc_unlabeled;
}