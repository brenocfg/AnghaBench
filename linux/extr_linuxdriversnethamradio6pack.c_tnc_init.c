#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sixpack {int /*<<< orphan*/  resync_t; TYPE_2__* tty; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write ) (TYPE_2__*,unsigned char*,int) ;} ;

/* Variables and functions */
 scalar_t__ SIXP_RESYNC_TIMEOUT ; 
 int /*<<< orphan*/  TNC_UNSYNC_STARTUP ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  tnc_set_sync_state (struct sixpack*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int tnc_init(struct sixpack *sp)
{
	unsigned char inbyte = 0xe8;

	tnc_set_sync_state(sp, TNC_UNSYNC_STARTUP);

	sp->tty->ops->write(sp->tty, &inbyte, 1);

	mod_timer(&sp->resync_t, jiffies + SIXP_RESYNC_TIMEOUT);

	return 0;
}