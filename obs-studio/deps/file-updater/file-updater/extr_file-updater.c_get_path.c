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
struct dstr {char* array; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_cat_ch (struct dstr*,char) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 char dstr_end (struct dstr*) ; 

__attribute__((used)) static char *get_path(const char *dir, const char *file)
{
	struct dstr str = {0};

	dstr_copy(&str, dir);

	if (str.array && dstr_end(&str) != '/' && dstr_end(&str) != '\\')
		dstr_cat_ch(&str, '/');

	dstr_cat(&str, file);
	return str.array;
}