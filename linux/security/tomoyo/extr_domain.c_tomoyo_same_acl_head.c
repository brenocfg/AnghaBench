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
struct tomoyo_acl_info {scalar_t__ type; scalar_t__ cond; } ;

/* Variables and functions */

__attribute__((used)) static inline bool tomoyo_same_acl_head(const struct tomoyo_acl_info *a,
					const struct tomoyo_acl_info *b)
{
	return a->type == b->type && a->cond == b->cond;
}