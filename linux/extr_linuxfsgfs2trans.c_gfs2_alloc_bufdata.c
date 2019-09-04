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
struct gfs2_log_operations {int dummy; } ;
struct gfs2_glock {int dummy; } ;
struct gfs2_bufdata {int /*<<< orphan*/  bd_list; struct gfs2_log_operations const* bd_ops; struct gfs2_glock* bd_gl; struct buffer_head* bd_bh; } ;
struct buffer_head {struct gfs2_bufdata* b_private; } ;

/* Variables and functions */
 int GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  gfs2_bufdata_cachep ; 
 struct gfs2_bufdata* kmem_cache_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct gfs2_bufdata *gfs2_alloc_bufdata(struct gfs2_glock *gl,
					       struct buffer_head *bh,
					       const struct gfs2_log_operations *lops)
{
	struct gfs2_bufdata *bd;

	bd = kmem_cache_zalloc(gfs2_bufdata_cachep, GFP_NOFS | __GFP_NOFAIL);
	bd->bd_bh = bh;
	bd->bd_gl = gl;
	bd->bd_ops = lops;
	INIT_LIST_HEAD(&bd->bd_list);
	bh->b_private = bd;
	return bd;
}