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
struct sk_buff {int dummy; } ;
struct rose_neigh {int /*<<< orphan*/ * ax25; TYPE_1__* dev; int /*<<< orphan*/  digipeat; int /*<<< orphan*/  callsign; } ;
typedef  int /*<<< orphan*/  ax25_cb ;
typedef  int /*<<< orphan*/  ax25_address ;
struct TYPE_2__ {scalar_t__ dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_cb_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ax25_send_frame (struct sk_buff*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ax25cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  null_ax25_address ; 
 int /*<<< orphan*/  rose_callsign ; 

__attribute__((used)) static int rose_send_frame(struct sk_buff *skb, struct rose_neigh *neigh)
{
	ax25_address *rose_call;
	ax25_cb *ax25s;

	if (ax25cmp(&rose_callsign, &null_ax25_address) == 0)
		rose_call = (ax25_address *)neigh->dev->dev_addr;
	else
		rose_call = &rose_callsign;

	ax25s = neigh->ax25;
	neigh->ax25 = ax25_send_frame(skb, 260, rose_call, &neigh->callsign, neigh->digipeat, neigh->dev);
	if (ax25s)
		ax25_cb_put(ax25s);

	return neigh->ax25 != NULL;
}