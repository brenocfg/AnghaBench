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
struct kbuffer {scalar_t__ data; } ;

/* Variables and functions */

__attribute__((used)) static int calc_index(struct kbuffer *kbuf, void *ptr)
{
	return (unsigned long)ptr - (unsigned long)kbuf->data;
}