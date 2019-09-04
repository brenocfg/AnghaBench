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
struct brcmf_msgbuf {scalar_t__ tx_pktids; TYPE_2__* drvr; scalar_t__ rx_pktids; } ;
struct TYPE_4__ {TYPE_1__* bus_if; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_msgbuf_release_array (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void brcmf_msgbuf_release_pktids(struct brcmf_msgbuf *msgbuf)
{
	if (msgbuf->rx_pktids)
		brcmf_msgbuf_release_array(msgbuf->drvr->bus_if->dev,
					   msgbuf->rx_pktids);
	if (msgbuf->tx_pktids)
		brcmf_msgbuf_release_array(msgbuf->drvr->bus_if->dev,
					   msgbuf->tx_pktids);
}