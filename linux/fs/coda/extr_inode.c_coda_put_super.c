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
struct venus_comm {int /*<<< orphan*/  vc_mutex; int /*<<< orphan*/ * vc_sb; } ;
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;

/* Variables and functions */
 struct venus_comm* coda_vcp (struct super_block*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void coda_put_super(struct super_block *sb)
{
	struct venus_comm *vcp = coda_vcp(sb);
	mutex_lock(&vcp->vc_mutex);
	vcp->vc_sb = NULL;
	sb->s_fs_info = NULL;
	mutex_unlock(&vcp->vc_mutex);
	mutex_destroy(&vcp->vc_mutex);

	pr_info("Bye bye.\n");
}