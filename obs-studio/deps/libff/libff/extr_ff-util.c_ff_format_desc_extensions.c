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
struct ff_format_desc {char const* extensions; } ;

/* Variables and functions */

const char *ff_format_desc_extensions(const struct ff_format_desc *format_desc)
{
	if (format_desc != NULL)
		return format_desc->extensions;
	else
		return NULL;
}