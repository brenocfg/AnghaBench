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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * state; } ;
struct qman_cgrs {TYPE_1__ q; } ;

/* Variables and functions */

__attribute__((used)) static inline void qman_cgrs_and(struct qman_cgrs *dest,
			const struct qman_cgrs *a, const struct qman_cgrs *b)
{
	int ret;
	u32 *_d = dest->q.state;
	const u32 *_a = a->q.state;
	const u32 *_b = b->q.state;

	for (ret = 0; ret < 8; ret++)
		*_d++ = *_a++ & *_b++;
}