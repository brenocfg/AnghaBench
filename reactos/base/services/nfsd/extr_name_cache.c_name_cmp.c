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
struct name_cache_entry {int component_len; int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int name_cmp(struct name_cache_entry *lhs, struct name_cache_entry *rhs)
{
    const int diff = rhs->component_len - lhs->component_len;
    return diff ? diff : strncmp(lhs->component, rhs->component, lhs->component_len);
}