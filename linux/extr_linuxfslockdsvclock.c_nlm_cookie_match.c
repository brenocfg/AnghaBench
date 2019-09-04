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
struct nlm_cookie {scalar_t__ len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int nlm_cookie_match(struct nlm_cookie *a, struct nlm_cookie *b)
{
	if (a->len != b->len)
		return 0;
	if (memcmp(a->data, b->data, a->len))
		return 0;
	return 1;
}