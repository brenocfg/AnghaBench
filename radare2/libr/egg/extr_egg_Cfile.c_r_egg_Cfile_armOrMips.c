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
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static inline bool r_egg_Cfile_armOrMips(const char *arch) {
	return (!strcmp (arch, "arm") || !strcmp (arch, "arm64") || !strcmp (arch, "aarch64")
	  	|| !strcmp (arch, "thumb") || !strcmp (arch, "arm32") || !strcmp (arch, "mips")
		|| !strcmp (arch, "mips32") || !strcmp (arch, "mips64"));
}