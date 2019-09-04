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
struct sock {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
typedef  int can_err_mask_t ;

/* Variables and functions */
 int CAN_ERR_FLAG ; 
 int /*<<< orphan*/  can_rx_unregister (struct net*,struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  raw_rcv ; 

__attribute__((used)) static inline void raw_disable_errfilter(struct net *net,
					 struct net_device *dev,
					 struct sock *sk,
					 can_err_mask_t err_mask)

{
	if (err_mask)
		can_rx_unregister(net, dev, 0, err_mask | CAN_ERR_FLAG,
				  raw_rcv, sk);
}