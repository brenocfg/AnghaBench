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
struct tun_struct {int flags; } ;
struct TYPE_4__ {TYPE_1__* sk; } ;
struct tun_file {TYPE_2__ socket; } ;
struct skb_shared_info {int dummy; } ;
struct TYPE_3__ {scalar_t__ sk_sndbuf; } ;

/* Variables and functions */
 int IFF_TAP ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ SKB_DATA_ALIGN (int) ; 
 int TUN_RX_PAD ; 
 int TUN_TYPE_MASK ; 

__attribute__((used)) static bool tun_can_build_skb(struct tun_struct *tun, struct tun_file *tfile,
			      int len, int noblock, bool zerocopy)
{
	if ((tun->flags & TUN_TYPE_MASK) != IFF_TAP)
		return false;

	if (tfile->socket.sk->sk_sndbuf != INT_MAX)
		return false;

	if (!noblock)
		return false;

	if (zerocopy)
		return false;

	if (SKB_DATA_ALIGN(len + TUN_RX_PAD) +
	    SKB_DATA_ALIGN(sizeof(struct skb_shared_info)) > PAGE_SIZE)
		return false;

	return true;
}