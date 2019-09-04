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
struct strref {int /*<<< orphan*/  len; int /*<<< orphan*/  array; } ;
struct dstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_ncat (struct dstr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dstr_cat_strref(struct dstr *dst, const struct strref *str)
{
	dstr_ncat(dst, str->array, str->len);
}