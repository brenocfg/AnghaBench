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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct iphdr {int ttl; int /*<<< orphan*/  check; } ;

/* Variables and functions */
 int OVS_MASKED (int,int,int) ; 
 int /*<<< orphan*/  csum_replace2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static void set_ip_ttl(struct sk_buff *skb, struct iphdr *nh, u8 new_ttl,
		       u8 mask)
{
	new_ttl = OVS_MASKED(nh->ttl, new_ttl, mask);

	csum_replace2(&nh->check, htons(nh->ttl << 8), htons(new_ttl << 8));
	nh->ttl = new_ttl;
}