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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int pskb_carve_inside_header (struct sk_buff*,int const,int,int /*<<< orphan*/ ) ; 
 int pskb_carve_inside_nonlinear (struct sk_buff*,int const,int,int /*<<< orphan*/ ) ; 
 int skb_headlen (struct sk_buff*) ; 

__attribute__((used)) static int pskb_carve(struct sk_buff *skb, const u32 len, gfp_t gfp)
{
	int headlen = skb_headlen(skb);

	if (len < headlen)
		return pskb_carve_inside_header(skb, len, headlen, gfp);
	else
		return pskb_carve_inside_nonlinear(skb, len, headlen, gfp);
}