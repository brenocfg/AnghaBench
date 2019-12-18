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
struct dstr {scalar_t__ array; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_copy_dstr (struct dstr*,struct dstr const*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 int /*<<< orphan*/  dstr_ncopy (struct dstr*,scalar_t__,size_t const) ; 

void dstr_mid(struct dstr *dst, const struct dstr *str, const size_t start,
	      const size_t count)
{
	struct dstr temp;
	dstr_init(&temp);
	dstr_copy_dstr(&temp, str);
	dstr_ncopy(dst, temp.array + start, count);
	dstr_free(&temp);
}