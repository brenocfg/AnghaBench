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
struct nsinfo {int /*<<< orphan*/  refcnt; scalar_t__ mntns_path; int /*<<< orphan*/  need_setns; int /*<<< orphan*/  nstgid; int /*<<< orphan*/  tgid; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 struct nsinfo* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct nsinfo*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strdup (scalar_t__) ; 

struct nsinfo *nsinfo__copy(struct nsinfo *nsi)
{
	struct nsinfo *nnsi;

	if (nsi == NULL)
		return NULL;

	nnsi = calloc(1, sizeof(*nnsi));
	if (nnsi != NULL) {
		nnsi->pid = nsi->pid;
		nnsi->tgid = nsi->tgid;
		nnsi->nstgid = nsi->nstgid;
		nnsi->need_setns = nsi->need_setns;
		if (nsi->mntns_path) {
			nnsi->mntns_path = strdup(nsi->mntns_path);
			if (!nnsi->mntns_path) {
				free(nnsi);
				return NULL;
			}
		}
		refcount_set(&nnsi->refcnt, 1);
	}

	return nnsi;
}