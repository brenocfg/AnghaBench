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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct nfs4_layoutcommit_data {TYPE_1__ res; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext_tree_mark_committed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bl_cleanup_layoutcommit(struct nfs4_layoutcommit_data *lcdata)
{
	ext_tree_mark_committed(&lcdata->args, lcdata->res.status);
}