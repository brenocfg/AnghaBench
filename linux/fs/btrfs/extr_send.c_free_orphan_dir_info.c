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
struct send_ctx {int /*<<< orphan*/  orphan_dirs; } ;
struct orphan_dir_info {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct orphan_dir_info*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_orphan_dir_info(struct send_ctx *sctx,
				 struct orphan_dir_info *odi)
{
	if (!odi)
		return;
	rb_erase(&odi->node, &sctx->orphan_dirs);
	kfree(odi);
}