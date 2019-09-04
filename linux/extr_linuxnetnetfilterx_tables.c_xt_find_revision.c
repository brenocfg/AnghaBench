#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPROTONOSUPPORT ; 
 int match_revfn (size_t,char const*,size_t,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int target_revfn (size_t,char const*,size_t,int*) ; 
 TYPE_1__* xt ; 

int xt_find_revision(u8 af, const char *name, u8 revision, int target,
		     int *err)
{
	int have_rev, best = -1;

	mutex_lock(&xt[af].mutex);
	if (target == 1)
		have_rev = target_revfn(af, name, revision, &best);
	else
		have_rev = match_revfn(af, name, revision, &best);
	mutex_unlock(&xt[af].mutex);

	/* Nothing at all?  Return 0 to try loading module. */
	if (best == -1) {
		*err = -ENOENT;
		return 0;
	}

	*err = best;
	if (!have_rev)
		*err = -EPROTONOSUPPORT;
	return 1;
}