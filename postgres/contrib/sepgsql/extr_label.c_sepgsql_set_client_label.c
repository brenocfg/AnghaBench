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
typedef  int /*<<< orphan*/  security_context_t ;
struct TYPE_4__ {int /*<<< orphan*/  label; int /*<<< orphan*/  subid; } ;
typedef  TYPE_1__ pending_label ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  CurTransactionContext ; 
 int /*<<< orphan*/  ERRCODE_INVALID_NAME ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEPG_CLASS_PROCESS ; 
 int /*<<< orphan*/  SEPG_PROCESS__DYNTRANSITION ; 
 int /*<<< orphan*/  SEPG_PROCESS__SETCURRENT ; 
 char* client_label_peer ; 
 int /*<<< orphan*/  client_label_pending ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* palloc0 (int) ; 
 int /*<<< orphan*/  pstrdup (char const*) ; 
 scalar_t__ security_check_context_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms_label (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 char const* sepgsql_get_client_label () ; 

__attribute__((used)) static void
sepgsql_set_client_label(const char *new_label)
{
	const char *tcontext;
	MemoryContext oldcxt;
	pending_label *plabel;

	/* Reset to the initial client label, if NULL */
	if (!new_label)
		tcontext = client_label_peer;
	else
	{
		if (security_check_context_raw((security_context_t) new_label) < 0)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_NAME),
					 errmsg("SELinux: invalid security label: \"%s\"",
							new_label)));
		tcontext = new_label;
	}

	/* Check process:{setcurrent} permission. */
	sepgsql_avc_check_perms_label(sepgsql_get_client_label(),
								  SEPG_CLASS_PROCESS,
								  SEPG_PROCESS__SETCURRENT,
								  NULL,
								  true);
	/* Check process:{dyntransition} permission. */
	sepgsql_avc_check_perms_label(tcontext,
								  SEPG_CLASS_PROCESS,
								  SEPG_PROCESS__DYNTRANSITION,
								  NULL,
								  true);

	/*
	 * Append the supplied new_label on the pending list until the current
	 * transaction is committed.
	 */
	oldcxt = MemoryContextSwitchTo(CurTransactionContext);

	plabel = palloc0(sizeof(pending_label));
	plabel->subid = GetCurrentSubTransactionId();
	if (new_label)
		plabel->label = pstrdup(new_label);
	client_label_pending = lappend(client_label_pending, plabel);

	MemoryContextSwitchTo(oldcxt);
}