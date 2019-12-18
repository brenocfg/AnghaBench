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
struct dstr {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_cat_dstr (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_copy_dstr (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_left (struct dstr*,struct dstr*,size_t) ; 
 int /*<<< orphan*/  dstr_right (struct dstr*,struct dstr*,size_t) ; 

__attribute__((used)) static void replace_text(struct dstr *str, size_t pos, size_t len,
			 const char *new_text)
{
	struct dstr front = {0};
	struct dstr back = {0};

	dstr_left(&front, str, pos);
	dstr_right(&back, str, pos + len);
	dstr_copy_dstr(str, &front);
	dstr_cat(str, new_text);
	dstr_cat_dstr(str, &back);
	dstr_free(&front);
	dstr_free(&back);
}