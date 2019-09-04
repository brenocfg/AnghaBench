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
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct request_sock {scalar_t__* saved_syn; } ;
struct TYPE_2__ {scalar_t__ save_syn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff const*) ; 
 scalar_t__ skb_network_header_len (struct sk_buff const*) ; 
 scalar_t__ tcp_hdrlen (struct sk_buff const*) ; 
 TYPE_1__* tcp_sk (struct sock const*) ; 

__attribute__((used)) static void tcp_reqsk_record_syn(const struct sock *sk,
				 struct request_sock *req,
				 const struct sk_buff *skb)
{
	if (tcp_sk(sk)->save_syn) {
		u32 len = skb_network_header_len(skb) + tcp_hdrlen(skb);
		u32 *copy;

		copy = kmalloc(len + sizeof(u32), GFP_ATOMIC);
		if (copy) {
			copy[0] = len;
			memcpy(&copy[1], skb_network_header(skb), len);
			req->saved_syn = copy;
		}
	}
}