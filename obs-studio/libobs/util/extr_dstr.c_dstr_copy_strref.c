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
struct dstr {scalar_t__ array; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_ncopy (struct dstr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dstr_copy_strref(struct dstr *dst, const struct strref *src)
{
	if (dst->array)
		dstr_free(dst);

	dstr_ncopy(dst, src->array, src->len);
}