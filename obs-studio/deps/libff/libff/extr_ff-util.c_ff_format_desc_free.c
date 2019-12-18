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
struct ff_format_desc {struct ff_format_desc* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (void*) ; 

void ff_format_desc_free(const struct ff_format_desc *format_desc)
{
	const struct ff_format_desc *desc = format_desc;
	while (desc != NULL) {
		const struct ff_format_desc *next = desc->next;
		av_free((void *)desc);
		desc = next;
	}
}