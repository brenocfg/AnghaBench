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
typedef  int /*<<< orphan*/  u8 ;
struct hci_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_chan*) ; 
 int /*<<< orphan*/  hci_chan_del (struct hci_chan*) ; 

void amp_destroy_logical_link(struct hci_chan *hchan, u8 reason)
{
	BT_DBG("hchan %p", hchan);

	hci_chan_del(hchan);
}