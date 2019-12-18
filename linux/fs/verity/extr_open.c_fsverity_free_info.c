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
struct TYPE_2__ {int /*<<< orphan*/  hashstate; } ;
struct fsverity_info {TYPE_1__ tree_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsverity_info_cachep ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fsverity_info*) ; 

void fsverity_free_info(struct fsverity_info *vi)
{
	if (!vi)
		return;
	kfree(vi->tree_params.hashstate);
	kmem_cache_free(fsverity_info_cachep, vi);
}