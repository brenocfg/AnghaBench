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
typedef  int /*<<< orphan*/  wchar_t ;
struct dstr {int /*<<< orphan*/  len; int /*<<< orphan*/  array; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_utf8_to_wcs_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

wchar_t *dstr_to_wcs(const struct dstr *str)
{
	wchar_t *dst;
	os_utf8_to_wcs_ptr(str->array, str->len, &dst);
	return dst;
}