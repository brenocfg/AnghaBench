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
struct nscookie {int oldns; int newns; scalar_t__ oldcwd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_NEWNS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chdir (scalar_t__) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  setns (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (scalar_t__*) ; 

void nsinfo__mountns_exit(struct nscookie *nc)
{
	if (nc == NULL || nc->oldns == -1 || nc->newns == -1 || !nc->oldcwd)
		return;

	setns(nc->oldns, CLONE_NEWNS);

	if (nc->oldcwd) {
		WARN_ON_ONCE(chdir(nc->oldcwd));
		zfree(&nc->oldcwd);
	}

	if (nc->oldns > -1) {
		close(nc->oldns);
		nc->oldns = -1;
	}

	if (nc->newns > -1) {
		close(nc->newns);
		nc->newns = -1;
	}
}