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
typedef  int /*<<< orphan*/  uncond ;
struct ip6t_ip6 {int dummy; } ;
struct ip6t_entry {int target_offset; int /*<<< orphan*/  ipv6; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,struct ip6t_ip6 const*,int) ; 

__attribute__((used)) static inline bool unconditional(const struct ip6t_entry *e)
{
	static const struct ip6t_ip6 uncond;

	return e->target_offset == sizeof(struct ip6t_entry) &&
	       memcmp(&e->ipv6, &uncond, sizeof(uncond)) == 0;
}