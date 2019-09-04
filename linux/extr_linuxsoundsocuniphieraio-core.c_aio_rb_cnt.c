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
typedef  int /*<<< orphan*/  u64 ;
struct uniphier_aio_sub {int /*<<< orphan*/  compr_bytes; int /*<<< orphan*/  rd_offs; int /*<<< orphan*/  wr_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_cnt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 aio_rb_cnt(struct uniphier_aio_sub *sub)
{
	return rb_cnt(sub->wr_offs, sub->rd_offs, sub->compr_bytes);
}