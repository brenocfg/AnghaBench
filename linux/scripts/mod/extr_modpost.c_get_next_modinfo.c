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
struct elf_info {char* modinfo; unsigned long modinfo_len; } ;

/* Variables and functions */
 char* next_string (char*,unsigned long*) ; 
 unsigned int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,unsigned int) ; 

__attribute__((used)) static char *get_next_modinfo(struct elf_info *info, const char *tag,
			      char *prev)
{
	char *p;
	unsigned int taglen = strlen(tag);
	char *modinfo = info->modinfo;
	unsigned long size = info->modinfo_len;

	if (prev) {
		size -= prev - modinfo;
		modinfo = next_string(prev, &size);
	}

	for (p = modinfo; p; p = next_string(p, &size)) {
		if (strncmp(p, tag, taglen) == 0 && p[taglen] == '=')
			return p + taglen + 1;
	}
	return NULL;
}