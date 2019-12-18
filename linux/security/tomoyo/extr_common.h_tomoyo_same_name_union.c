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
struct tomoyo_name_union {scalar_t__ filename; scalar_t__ group; } ;

/* Variables and functions */

__attribute__((used)) static inline bool tomoyo_same_name_union
(const struct tomoyo_name_union *a, const struct tomoyo_name_union *b)
{
	return a->filename == b->filename && a->group == b->group;
}