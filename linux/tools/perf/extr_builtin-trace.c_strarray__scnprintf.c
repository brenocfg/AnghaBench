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
struct strarray {int offset; int nr_entries; char* prefix; int /*<<< orphan*/ ** entries; } ;

/* Variables and functions */
 size_t scnprintf (char*,size_t,char const*,...) ; 

size_t strarray__scnprintf(struct strarray *sa, char *bf, size_t size, const char *intfmt, bool show_prefix, int val)
{
	int idx = val - sa->offset;

	if (idx < 0 || idx >= sa->nr_entries || sa->entries[idx] == NULL) {
		size_t printed = scnprintf(bf, size, intfmt, val);
		if (show_prefix)
			printed += scnprintf(bf + printed, size - printed, " /* %s??? */", sa->prefix);
		return printed;
	}

	return scnprintf(bf, size, "%s%s", show_prefix ? sa->prefix : "", sa->entries[idx]);
}