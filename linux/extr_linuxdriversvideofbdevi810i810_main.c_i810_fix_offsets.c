#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int offset; int size; } ;
struct TYPE_7__ {int offset; int size; } ;
struct TYPE_6__ {int size; int offset; } ;
struct TYPE_5__ {int size; } ;
struct i810fb_par {TYPE_4__ cursor_heap; TYPE_3__ iring; TYPE_2__ fb; TYPE_1__ aperture; } ;

/* Variables and functions */
 int RINGBUFFER_SIZE ; 
 int v_offset_default ; 
 int vram ; 

__attribute__((used)) static void i810_fix_offsets(struct i810fb_par *par)
{
	if (vram + 1 > par->aperture.size >> 20)
		vram = (par->aperture.size >> 20) - 1;
	if (v_offset_default > (par->aperture.size >> 20))
		v_offset_default = (par->aperture.size >> 20);
	if (vram + v_offset_default + 1 > par->aperture.size >> 20)
		v_offset_default = (par->aperture.size >> 20) - (vram + 1);

	par->fb.size = vram << 20;
	par->fb.offset = v_offset_default << 20;
	par->fb.offset >>= 12;

	par->iring.offset = par->fb.offset + (par->fb.size >> 12);
	par->iring.size = RINGBUFFER_SIZE;

	par->cursor_heap.offset = par->iring.offset + (RINGBUFFER_SIZE >> 12);
	par->cursor_heap.size = 4096;
}