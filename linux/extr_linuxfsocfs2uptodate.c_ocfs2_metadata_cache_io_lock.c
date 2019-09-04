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
struct ocfs2_caching_info {TYPE_1__* ci_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* co_io_lock ) (struct ocfs2_caching_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct ocfs2_caching_info*) ; 

void ocfs2_metadata_cache_io_lock(struct ocfs2_caching_info *ci)
{
	BUG_ON(!ci || !ci->ci_ops);

	ci->ci_ops->co_io_lock(ci);
}