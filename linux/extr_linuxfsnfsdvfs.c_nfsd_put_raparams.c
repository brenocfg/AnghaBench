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
struct raparms {size_t p_hindex; int p_set; int /*<<< orphan*/  p_count; int /*<<< orphan*/  p_ra; } ;
struct raparm_hbucket {int /*<<< orphan*/  pb_lock; } ;
struct file {int /*<<< orphan*/  f_ra; } ;

/* Variables and functions */
 struct raparm_hbucket* raparm_hash ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfsd_put_raparams(struct file *file, struct raparms *ra)
{
	struct raparm_hbucket *rab = &raparm_hash[ra->p_hindex];

	spin_lock(&rab->pb_lock);
	ra->p_ra = file->f_ra;
	ra->p_set = 1;
	ra->p_count--;
	spin_unlock(&rab->pb_lock);
}