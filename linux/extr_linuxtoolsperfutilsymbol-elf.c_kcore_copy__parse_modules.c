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
struct kcore_copy_info {int dummy; } ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  kcore_copy__process_modules ; 
 scalar_t__ modules__parse (char*,struct kcore_copy_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*) ; 
 scalar_t__ symbol__restricted_filename (char*,char*) ; 

__attribute__((used)) static int kcore_copy__parse_modules(struct kcore_copy_info *kci,
				     const char *dir)
{
	char modules_filename[PATH_MAX];

	scnprintf(modules_filename, PATH_MAX, "%s/modules", dir);

	if (symbol__restricted_filename(modules_filename, "/proc/modules"))
		return -1;

	if (modules__parse(modules_filename, kci,
			   kcore_copy__process_modules) < 0)
		return -1;

	return 0;
}