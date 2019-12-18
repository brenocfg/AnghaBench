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
struct attr_cache_entry {scalar_t__ fileid; } ;

/* Variables and functions */

int attr_cmp(struct attr_cache_entry *lhs, struct attr_cache_entry *rhs)
{
    return lhs->fileid < rhs->fileid ? -1 : lhs->fileid > rhs->fileid;
}