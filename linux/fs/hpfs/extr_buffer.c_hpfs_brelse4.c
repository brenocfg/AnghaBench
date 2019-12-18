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
struct quad_buffer_head {scalar_t__ data; TYPE_1__** bh; } ;
struct TYPE_2__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

void hpfs_brelse4(struct quad_buffer_head *qbh)
{
	if (unlikely(qbh->data != qbh->bh[0]->b_data))
		kfree(qbh->data);
	brelse(qbh->bh[0]);
	brelse(qbh->bh[1]);
	brelse(qbh->bh[2]);
	brelse(qbh->bh[3]);
}