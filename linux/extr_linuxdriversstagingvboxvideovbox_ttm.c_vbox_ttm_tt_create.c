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
typedef  int /*<<< orphan*/  u32 ;
struct ttm_tt {int /*<<< orphan*/ * func; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ttm_tt*) ; 
 struct ttm_tt* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ttm_tt_init (struct ttm_tt*,struct ttm_buffer_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbox_tt_backend_func ; 

__attribute__((used)) static struct ttm_tt *vbox_ttm_tt_create(struct ttm_buffer_object *bo,
					 u32 page_flags)
{
	struct ttm_tt *tt;

	tt = kzalloc(sizeof(*tt), GFP_KERNEL);
	if (!tt)
		return NULL;

	tt->func = &vbox_tt_backend_func;
	if (ttm_tt_init(tt, bo, page_flags)) {
		kfree(tt);
		return NULL;
	}

	return tt;
}