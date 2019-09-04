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
struct nsinfo {int need_setns; int /*<<< orphan*/  refcnt; scalar_t__ nstgid; scalar_t__ tgid; scalar_t__ pid; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 struct nsinfo* calloc (int,int) ; 
 int nsinfo__init (struct nsinfo*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

struct nsinfo *nsinfo__new(pid_t pid)
{
	struct nsinfo *nsi;

	if (pid == 0)
		return NULL;

	nsi = calloc(1, sizeof(*nsi));
	if (nsi != NULL) {
		nsi->pid = pid;
		nsi->tgid = pid;
		nsi->nstgid = pid;
		nsi->need_setns = false;
		/* Init may fail if the process exits while we're trying to look
		 * at its proc information.  In that case, save the pid but
		 * don't try to enter the namespace.
		 */
		if (nsinfo__init(nsi) == -1)
			nsi->need_setns = false;

		refcount_set(&nsi->refcnt, 1);
	}

	return nsi;
}