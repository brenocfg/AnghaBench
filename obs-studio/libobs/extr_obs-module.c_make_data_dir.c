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
struct dstr {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 char dstr_end (struct dstr*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char const*) ; 
 int /*<<< orphan*/  dstr_resize (struct dstr*,scalar_t__) ; 

__attribute__((used)) static inline void make_data_dir(struct dstr *parsed_data_dir,
				 const char *data_dir, const char *name)
{
	dstr_copy(parsed_data_dir, data_dir);
	dstr_replace(parsed_data_dir, "%module%", name);
	if (dstr_end(parsed_data_dir) == '/')
		dstr_resize(parsed_data_dir, parsed_data_dir->len - 1);
}