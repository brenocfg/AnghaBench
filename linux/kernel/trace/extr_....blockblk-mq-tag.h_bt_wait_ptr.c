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
struct sbq_wait_state {int dummy; } ;
struct sbitmap_queue {struct sbq_wait_state* ws; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  wait_index; } ;

/* Variables and functions */
 struct sbq_wait_state* sbq_wait_ptr (struct sbitmap_queue*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct sbq_wait_state *bt_wait_ptr(struct sbitmap_queue *bt,
						 struct blk_mq_hw_ctx *hctx)
{
	if (!hctx)
		return &bt->ws[0];
	return sbq_wait_ptr(bt, &hctx->wait_index);
}