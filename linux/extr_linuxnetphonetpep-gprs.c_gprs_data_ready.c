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
struct sock {struct gprs_dev* sk_user_data; } ;
struct sk_buff {int dummy; } ;
struct gprs_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gprs_recv (struct gprs_dev*,struct sk_buff*) ; 
 struct sk_buff* pep_read (struct sock*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 

__attribute__((used)) static void gprs_data_ready(struct sock *sk)
{
	struct gprs_dev *gp = sk->sk_user_data;
	struct sk_buff *skb;

	while ((skb = pep_read(sk)) != NULL) {
		skb_orphan(skb);
		gprs_recv(gp, skb);
	}
}