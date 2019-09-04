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
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct net2272_ep {TYPE_2__ ep; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALT_NAK_OUT_PACKETS ; 
 int /*<<< orphan*/  EP_RSPSET ; 
 int /*<<< orphan*/  EP_STAT0 ; 
 int NAK_OUT_PACKETS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int) ; 
 int net2272_ep_read (struct net2272_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net2272_ep_write (struct net2272_ep*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void assert_out_naking(struct net2272_ep *ep, const char *where)
{
	u8 tmp;

#ifndef DEBUG
	return;
#endif

	tmp = net2272_ep_read(ep, EP_STAT0);
	if ((tmp & (1 << NAK_OUT_PACKETS)) == 0) {
		dev_dbg(ep->dev->dev, "%s %s %02x !NAK\n",
			ep->ep.name, where, tmp);
		net2272_ep_write(ep, EP_RSPSET, 1 << ALT_NAK_OUT_PACKETS);
	}
}