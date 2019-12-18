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
struct discard_info {scalar_t__ lstart; unsigned int len; } ;

/* Variables and functions */

__attribute__((used)) static inline bool __is_discard_mergeable(struct discard_info *back,
			struct discard_info *front, unsigned int max_len)
{
	return (back->lstart + back->len == front->lstart) &&
		(back->len + front->len <= max_len);
}