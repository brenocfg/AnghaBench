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

/* Variables and functions */
 int PATH_MAX ; 
 int kcore_copy__compare_files (char*,char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*,char const*) ; 

__attribute__((used)) static int kcore_copy__compare_file(const char *from_dir, const char *to_dir,
				    const char *name)
{
	char from_filename[PATH_MAX];
	char to_filename[PATH_MAX];

	scnprintf(from_filename, PATH_MAX, "%s/%s", from_dir, name);
	scnprintf(to_filename, PATH_MAX, "%s/%s", to_dir, name);

	return kcore_copy__compare_files(from_filename, to_filename);
}