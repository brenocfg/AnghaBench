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
struct alloc_func {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */

__attribute__((used)) static int callcmp(const void *a, const void *b)
{
	const struct alloc_func *fa = a;
	const struct alloc_func *fb = b;

	if (fb->start <= fa->start && fa->end < fb->end)
		return 0;

	if (fa->start > fb->start)
		return 1;
	else
		return -1;
}