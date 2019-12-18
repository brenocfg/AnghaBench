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
struct zip_string {scalar_t__ length; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
_zip_string_equal(const struct zip_string *a, const struct zip_string *b)
{
    if (a == NULL || b == NULL)
	return a == b;

    if (a->length != b->length)
	return 0;

    /* XXX: encoding */

    return (memcmp(a->raw, b->raw, a->length) == 0);
}