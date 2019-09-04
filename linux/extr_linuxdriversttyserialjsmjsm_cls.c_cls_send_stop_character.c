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
struct jsm_channel {scalar_t__ ch_stopc; TYPE_1__* ch_cls_uart; int /*<<< orphan*/  ch_xoff_sends; } ;
struct TYPE_2__ {int /*<<< orphan*/  txrx; } ;

/* Variables and functions */
 scalar_t__ __DISABLED_CHAR ; 
 int /*<<< orphan*/  writeb (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cls_send_stop_character(struct jsm_channel *ch)
{
	if (!ch)
		return;

	if (ch->ch_stopc != __DISABLED_CHAR) {
		ch->ch_xoff_sends++;
		writeb(ch->ch_stopc, &ch->ch_cls_uart->txrx);
	}
}