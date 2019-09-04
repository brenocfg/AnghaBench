#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int match_size; } ;
struct xt_entry_match {TYPE_1__ u; } ;
typedef  scalar_t__ pos ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int xt_check_entry_match(const char *match, const char *target,
				const size_t alignment)
{
	const struct xt_entry_match *pos;
	int length = target - match;

	if (length == 0) /* no matches */
		return 0;

	pos = (struct xt_entry_match *)match;
	do {
		if ((unsigned long)pos % alignment)
			return -EINVAL;

		if (length < (int)sizeof(struct xt_entry_match))
			return -EINVAL;

		if (pos->u.match_size < sizeof(struct xt_entry_match))
			return -EINVAL;

		if (pos->u.match_size > length)
			return -EINVAL;

		length -= pos->u.match_size;
		pos = ((void *)((char *)(pos) + (pos)->u.match_size));
	} while (length > 0);

	return 0;
}