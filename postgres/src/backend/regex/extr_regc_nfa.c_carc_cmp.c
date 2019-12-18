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
struct carc {scalar_t__ co; scalar_t__ to; } ;

/* Variables and functions */

__attribute__((used)) static int
carc_cmp(const void *a, const void *b)
{
	const struct carc *aa = (const struct carc *) a;
	const struct carc *bb = (const struct carc *) b;

	if (aa->co < bb->co)
		return -1;
	if (aa->co > bb->co)
		return +1;
	if (aa->to < bb->to)
		return -1;
	if (aa->to > bb->to)
		return +1;
	return 0;
}