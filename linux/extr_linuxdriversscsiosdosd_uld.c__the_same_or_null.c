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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static inline bool _the_same_or_null(const u8 *a1, unsigned a1_len,
				     const u8 *a2, unsigned a2_len)
{
	if (!a2_len) /* User string is Empty means don't care */
		return true;

	if (a1_len != a2_len)
		return false;

	return 0 == memcmp(a1, a2, a1_len);
}