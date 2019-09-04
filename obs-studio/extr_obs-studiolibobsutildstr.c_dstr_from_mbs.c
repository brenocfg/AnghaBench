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
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  os_mbs_to_utf8_ptr (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dstr_from_mbs(struct dstr *dst, const char *mbstr)
{
	dstr_free(dst);
	dst->len = os_mbs_to_utf8_ptr(mbstr, 0, &dst->array);
}