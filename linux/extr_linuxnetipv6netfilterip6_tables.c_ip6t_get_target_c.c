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
struct xt_entry_target {int dummy; } ;
struct ip6t_entry {int dummy; } ;

/* Variables and functions */
 struct xt_entry_target const* ip6t_get_target (struct ip6t_entry*) ; 

__attribute__((used)) static inline const struct xt_entry_target *
ip6t_get_target_c(const struct ip6t_entry *e)
{
	return ip6t_get_target((struct ip6t_entry *)e);
}