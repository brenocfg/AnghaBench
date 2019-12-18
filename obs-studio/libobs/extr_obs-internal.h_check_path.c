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
struct dstr {int /*<<< orphan*/  array; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int os_file_exists (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool check_path(const char *data, const char *path,
			      struct dstr *output)
{
	dstr_copy(output, path);
	dstr_cat(output, data);

	return os_file_exists(output->array);
}