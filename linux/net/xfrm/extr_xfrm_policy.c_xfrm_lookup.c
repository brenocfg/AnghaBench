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
struct net {int dummy; } ;
struct flowi {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 struct dst_entry* xfrm_lookup_with_ifid (struct net*,struct dst_entry*,struct flowi const*,struct sock const*,int,int /*<<< orphan*/ ) ; 

struct dst_entry *xfrm_lookup(struct net *net, struct dst_entry *dst_orig,
			      const struct flowi *fl, const struct sock *sk,
			      int flags)
{
	return xfrm_lookup_with_ifid(net, dst_orig, fl, sk, flags, 0);
}