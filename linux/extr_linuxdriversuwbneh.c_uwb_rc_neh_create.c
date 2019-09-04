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
struct uwb_rc {int ctx_roll; int /*<<< orphan*/  ctx_bm; int /*<<< orphan*/  neh_list; int /*<<< orphan*/  neh_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void uwb_rc_neh_create(struct uwb_rc *rc)
{
	spin_lock_init(&rc->neh_lock);
	INIT_LIST_HEAD(&rc->neh_list);
	set_bit(0, rc->ctx_bm);		/* 0 is reserved (see [WUSB] table 8-65) */
	set_bit(0xff, rc->ctx_bm);	/* and 0xff is invalid */
	rc->ctx_roll = 1;
}