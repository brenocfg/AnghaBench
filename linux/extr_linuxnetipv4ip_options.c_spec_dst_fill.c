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
struct sk_buff {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ fib_compute_spec_dst (struct sk_buff*) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spec_dst_fill(__be32 *spec_dst, struct sk_buff *skb)
{
	if (*spec_dst == htonl(INADDR_ANY))
		*spec_dst = fib_compute_spec_dst(skb);
}