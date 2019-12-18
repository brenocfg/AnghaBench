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
struct kasan_access_info {int /*<<< orphan*/  access_addr; } ;

/* Variables and functions */
 scalar_t__ addr_has_shadow (int /*<<< orphan*/ ) ; 
 char const* get_shadow_bug_type (struct kasan_access_info*) ; 
 char const* get_wild_bug_type (struct kasan_access_info*) ; 

const char *get_bug_type(struct kasan_access_info *info)
{
	if (addr_has_shadow(info->access_addr))
		return get_shadow_bug_type(info);
	return get_wild_bug_type(info);
}