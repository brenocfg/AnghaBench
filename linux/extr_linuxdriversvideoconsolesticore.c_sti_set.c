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
typedef  int /*<<< orphan*/  u8 ;
struct sti_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  glob_cfg; int /*<<< orphan*/  block_move; TYPE_1__* sti_data; } ;
struct sti_blkmv_outptr {int dummy; } ;
struct sti_blkmv_inptr {int src_x; int src_y; int dest_x; int dest_y; int width; int height; int /*<<< orphan*/  bg_color; int /*<<< orphan*/  fg_color; } ;
typedef  int s32 ;
struct TYPE_2__ {struct sti_blkmv_outptr blkmv_outptr; struct sti_blkmv_inptr blkmv_inptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_blkmv_flags ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sti_call (struct sti_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sti_blkmv_inptr*,struct sti_blkmv_outptr*,int /*<<< orphan*/ ) ; 

void
sti_set(struct sti_struct *sti, int src_y, int src_x,
	int height, int width, u8 color)
{
	struct sti_blkmv_inptr *inptr = &sti->sti_data->blkmv_inptr;
	struct sti_blkmv_inptr inptr_default = {
		.fg_color	= color,
		.bg_color	= color,
		.src_x		= src_x,
		.src_y		= src_y,
		.dest_x		= src_x,
		.dest_y		= src_y,
		.width		= width,
		.height		= height,
	};
	struct sti_blkmv_outptr *outptr = &sti->sti_data->blkmv_outptr;
	s32 ret;
	unsigned long flags;
	
	do {
		spin_lock_irqsave(&sti->lock, flags);
		*inptr = inptr_default;
		ret = sti_call(sti, sti->block_move, &clear_blkmv_flags,
			inptr, outptr, sti->glob_cfg);
		spin_unlock_irqrestore(&sti->lock, flags);
	} while (ret == 1);
}