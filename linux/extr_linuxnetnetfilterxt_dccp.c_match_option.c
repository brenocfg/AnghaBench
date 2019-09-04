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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sk_buff {int dummy; } ;
struct dccp_hdr {int dummy; } ;

/* Variables and functions */
 int dccp_find_option (int /*<<< orphan*/ ,struct sk_buff const*,unsigned int,struct dccp_hdr const*,int*) ; 

__attribute__((used)) static inline bool
match_option(u_int8_t option, const struct sk_buff *skb, unsigned int protoff,
	     const struct dccp_hdr *dh, bool *hotdrop)
{
	return dccp_find_option(option, skb, protoff, dh, hotdrop);
}