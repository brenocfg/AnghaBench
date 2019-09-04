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
struct raw_sock {int /*<<< orphan*/  err_mask; int /*<<< orphan*/  count; int /*<<< orphan*/  filter; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_disable_errfilter (struct net*,struct net_device*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_disable_filters (struct net*,struct net_device*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct raw_sock* raw_sk (struct sock*) ; 

__attribute__((used)) static inline void raw_disable_allfilters(struct net *net,
					  struct net_device *dev,
					  struct sock *sk)
{
	struct raw_sock *ro = raw_sk(sk);

	raw_disable_filters(net, dev, sk, ro->filter, ro->count);
	raw_disable_errfilter(net, dev, sk, ro->err_mask);
}