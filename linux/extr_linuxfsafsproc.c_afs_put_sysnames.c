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
struct afs_sysnames {int nr; scalar_t__* subs; scalar_t__ blank; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 scalar_t__ afs_init_sysname ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void afs_put_sysnames(struct afs_sysnames *sysnames)
{
	int i;

	if (sysnames && refcount_dec_and_test(&sysnames->usage)) {
		for (i = 0; i < sysnames->nr; i++)
			if (sysnames->subs[i] != afs_init_sysname &&
			    sysnames->subs[i] != sysnames->blank)
				kfree(sysnames->subs[i]);
	}
}