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
struct scm_fp_list {int count; int /*<<< orphan*/  user; int /*<<< orphan*/ * fp; } ;
struct scm_cookie {struct scm_fp_list* fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scm_fp_list*) ; 

void __scm_destroy(struct scm_cookie *scm)
{
	struct scm_fp_list *fpl = scm->fp;
	int i;

	if (fpl) {
		scm->fp = NULL;
		for (i=fpl->count-1; i>=0; i--)
			fput(fpl->fp[i]);
		free_uid(fpl->user);
		kfree(fpl);
	}
}