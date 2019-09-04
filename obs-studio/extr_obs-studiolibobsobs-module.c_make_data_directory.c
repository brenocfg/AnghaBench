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
 scalar_t__ astrcmpi_n (char const*,char*,int) ; 
 int /*<<< orphan*/  make_data_dir (struct dstr*,char const*,char const*) ; 
 int os_file_exists (char*) ; 

__attribute__((used)) static char *make_data_directory(const char *module_name, const char *data_dir)
{
	struct dstr parsed_data_dir = {0};
	bool found = false;

	make_data_dir(&parsed_data_dir, data_dir, module_name);

	found = os_file_exists(parsed_data_dir.array);

	if (!found && astrcmpi_n(module_name, "lib", 3) == 0)
		make_data_dir(&parsed_data_dir, data_dir, module_name + 3);

	return parsed_data_dir.array;
}