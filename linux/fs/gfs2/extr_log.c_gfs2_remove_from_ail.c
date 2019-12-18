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
struct gfs2_bufdata {int /*<<< orphan*/  bd_bh; TYPE_1__* bd_gl; int /*<<< orphan*/  bd_ail_gl_list; int /*<<< orphan*/  bd_ail_st_list; int /*<<< orphan*/ * bd_tr; } ;
struct TYPE_2__ {int /*<<< orphan*/  gl_ail_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfs2_remove_from_ail(struct gfs2_bufdata *bd)
{
	bd->bd_tr = NULL;
	list_del_init(&bd->bd_ail_st_list);
	list_del_init(&bd->bd_ail_gl_list);
	atomic_dec(&bd->bd_gl->gl_ail_count);
	brelse(bd->bd_bh);
}