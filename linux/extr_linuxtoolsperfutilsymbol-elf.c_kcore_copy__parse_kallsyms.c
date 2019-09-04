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
 scalar_t__ kallsyms__parse (char*,struct kcore_copy_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcore_copy__process_kallsyms ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*) ; 
 scalar_t__ symbol__restricted_filename (char*,char*) ; 

__attribute__((used)) static int kcore_copy__parse_kallsyms(struct kcore_copy_info *kci,
				      const char *dir)
{
	char kallsyms_filename[PATH_MAX];

	scnprintf(kallsyms_filename, PATH_MAX, "%s/kallsyms", dir);

	if (symbol__restricted_filename(kallsyms_filename, "/proc/kallsyms"))
		return -1;

	if (kallsyms__parse(kallsyms_filename, kci,
			    kcore_copy__process_kallsyms) < 0)
		return -1;

	return 0;
}