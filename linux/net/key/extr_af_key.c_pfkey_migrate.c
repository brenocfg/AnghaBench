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
struct sk_buff {int dummy; } ;
struct sadb_msg {int dummy; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 

__attribute__((used)) static int pfkey_migrate(struct sock *sk, struct sk_buff *skb,
			 const struct sadb_msg *hdr, void * const *ext_hdrs)
{
	return -ENOPROTOOPT;
}