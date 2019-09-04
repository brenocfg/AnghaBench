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
struct dstr {int /*<<< orphan*/  len; int /*<<< orphan*/  array; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_mbs_to_utf8_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 

char *dstr_to_mbs(const struct dstr *str)
{
	char *dst;
	os_mbs_to_utf8_ptr(str->array, str->len, &dst);
	return dst;
}