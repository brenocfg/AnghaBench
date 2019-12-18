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
struct dstr {scalar_t__ array; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,scalar_t__) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_left (struct dstr*,struct dstr*,size_t) ; 

__attribute__((used)) static void erase_ch(struct dstr *str, size_t pos)
{
	struct dstr new_str = {0};
	dstr_left(&new_str, str, pos);
	dstr_cat(&new_str, str->array + pos + 1);
	dstr_free(str);
	*str = new_str;
}