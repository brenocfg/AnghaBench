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
struct il_queue {int n_bd; int n_win; int low_mark; int high_mark; scalar_t__ read_ptr; scalar_t__ write_ptr; int /*<<< orphan*/  id; } ;
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int TFD_QUEUE_SIZE_MAX ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 

__attribute__((used)) static int
il_queue_init(struct il_priv *il, struct il_queue *q, int slots, u32 id)
{
	/*
	 * TFD_QUEUE_SIZE_MAX must be power-of-two size, otherwise
	 * il_queue_inc_wrap and il_queue_dec_wrap are broken.
	 */
	BUILD_BUG_ON(TFD_QUEUE_SIZE_MAX & (TFD_QUEUE_SIZE_MAX - 1));
	/* FIXME: remove q->n_bd */
	q->n_bd = TFD_QUEUE_SIZE_MAX;

	q->n_win = slots;
	q->id = id;

	/* slots_must be power-of-two size, otherwise
	 * il_get_cmd_idx is broken. */
	BUG_ON(!is_power_of_2(slots));

	q->low_mark = q->n_win / 4;
	if (q->low_mark < 4)
		q->low_mark = 4;

	q->high_mark = q->n_win / 8;
	if (q->high_mark < 2)
		q->high_mark = 2;

	q->write_ptr = q->read_ptr = 0;

	return 0;
}