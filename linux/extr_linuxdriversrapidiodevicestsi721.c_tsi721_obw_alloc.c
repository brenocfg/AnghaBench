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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct tsi721_obw_bar {scalar_t__ base; scalar_t__ size; int /*<<< orphan*/  free; } ;
struct tsi721_ob_win {int active; scalar_t__ base; scalar_t__ size; struct tsi721_obw_bar* pbar; } ;
struct tsi721_device {int /*<<< orphan*/  obwin_cnt; TYPE_1__* pdev; struct tsi721_ob_win* ob_win; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,scalar_t__) ; 
 int EIO ; 
 int ENOMEM ; 
 int TSI721_IBWIN_NUM ; 
 scalar_t__ TSI721_PC2SR_ZONES ; 
 int /*<<< orphan*/  tsi_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
tsi721_obw_alloc(struct tsi721_device *priv, struct tsi721_obw_bar *pbar,
		 u32 size, int *win_id)
{
	u64 win_base;
	u64 bar_base;
	u64 bar_end;
	u32 align;
	struct tsi721_ob_win *win;
	struct tsi721_ob_win *new_win = NULL;
	int new_win_idx = -1;
	int i = 0;

	bar_base = pbar->base;
	bar_end =  bar_base + pbar->size;
	win_base = bar_base;
	align = size/TSI721_PC2SR_ZONES;

	while (i < TSI721_IBWIN_NUM) {
		for (i = 0; i < TSI721_IBWIN_NUM; i++) {
			if (!priv->ob_win[i].active) {
				if (new_win == NULL) {
					new_win = &priv->ob_win[i];
					new_win_idx = i;
				}
				continue;
			}

			/*
			 * If this window belongs to the current BAR check it
			 * for overlap
			 */
			win = &priv->ob_win[i];

			if (win->base >= bar_base && win->base < bar_end) {
				if (win_base < (win->base + win->size) &&
						(win_base + size) > win->base) {
					/* Overlap detected */
					win_base = win->base + win->size;
					win_base = ALIGN(win_base, align);
					break;
				}
			}
		}
	}

	if (win_base + size > bar_end)
		return -ENOMEM;

	if (!new_win) {
		tsi_err(&priv->pdev->dev, "OBW count tracking failed");
		return -EIO;
	}

	new_win->active = true;
	new_win->base = win_base;
	new_win->size = size;
	new_win->pbar = pbar;
	priv->obwin_cnt--;
	pbar->free -= size;
	*win_id = new_win_idx;
	return 0;
}