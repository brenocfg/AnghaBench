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
typedef  int /*<<< orphan*/  zip_uint16_t ;
struct zip_string {int /*<<< orphan*/  length; } ;

/* Variables and functions */

zip_uint16_t
_zip_string_length(const struct zip_string *s)
{
    if (s == NULL)
	return 0;

    return s->length;
}