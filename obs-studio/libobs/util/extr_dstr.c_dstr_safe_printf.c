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
struct dstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char const*) ; 

void dstr_safe_printf(struct dstr *dst, const char *format, const char *val1,
		      const char *val2, const char *val3, const char *val4)
{
	dstr_copy(dst, format);
	if (val1)
		dstr_replace(dst, "$1", val1);
	if (val2)
		dstr_replace(dst, "$2", val2);
	if (val3)
		dstr_replace(dst, "$3", val3);
	if (val4)
		dstr_replace(dst, "$4", val4);
}