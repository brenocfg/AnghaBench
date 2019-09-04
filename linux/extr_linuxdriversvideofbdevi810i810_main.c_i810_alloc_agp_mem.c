#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_5__* i810_cursor_memory; TYPE_5__* i810_fb_memory; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  physical; int /*<<< orphan*/  offset; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {int size; } ;
struct i810fb_par {TYPE_4__ i810_gtt; TYPE_3__ cursor_heap; TYPE_2__ fb; int /*<<< orphan*/  dev; TYPE_1__ iring; } ;
struct fb_info {struct i810fb_par* par; } ;
struct agp_bridge_data {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  physical; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_NORMAL_MEMORY ; 
 int /*<<< orphan*/  AGP_PHYSICAL_MEMORY ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 void* agp_allocate_memory (struct agp_bridge_data*,int,int /*<<< orphan*/ ) ; 
 struct agp_bridge_data* agp_backend_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_backend_release (struct agp_bridge_data*) ; 
 scalar_t__ agp_bind_memory (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i810_fix_offsets (struct i810fb_par*) ; 
 int /*<<< orphan*/  i810_fix_pointers (struct i810fb_par*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int i810_alloc_agp_mem(struct fb_info *info)
{
	struct i810fb_par *par = info->par;
	int size;
	struct agp_bridge_data *bridge;
	
	i810_fix_offsets(par);
	size = par->fb.size + par->iring.size;

	if (!(bridge = agp_backend_acquire(par->dev))) {
		printk("i810fb_alloc_fbmem: cannot acquire agpgart\n");
		return -ENODEV;
	}
	if (!(par->i810_gtt.i810_fb_memory = 
	      agp_allocate_memory(bridge, size >> 12, AGP_NORMAL_MEMORY))) {
		printk("i810fb_alloc_fbmem: can't allocate framebuffer "
		       "memory\n");
		agp_backend_release(bridge);
		return -ENOMEM;
	}
	if (agp_bind_memory(par->i810_gtt.i810_fb_memory,
			    par->fb.offset)) {
		printk("i810fb_alloc_fbmem: can't bind framebuffer memory\n");
		agp_backend_release(bridge);
		return -EBUSY;
	}	
	
	if (!(par->i810_gtt.i810_cursor_memory = 
	      agp_allocate_memory(bridge, par->cursor_heap.size >> 12,
				  AGP_PHYSICAL_MEMORY))) {
		printk("i810fb_alloc_cursormem:  can't allocate "
		       "cursor memory\n");
		agp_backend_release(bridge);
		return -ENOMEM;
	}
	if (agp_bind_memory(par->i810_gtt.i810_cursor_memory,
			    par->cursor_heap.offset)) {
		printk("i810fb_alloc_cursormem: cannot bind cursor memory\n");
		agp_backend_release(bridge);
		return -EBUSY;
	}	

	par->cursor_heap.physical = par->i810_gtt.i810_cursor_memory->physical;

	i810_fix_pointers(par);

	agp_backend_release(bridge);

	return 0;
}