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
typedef  int ut32 ;

/* Variables and functions */
 int VER_FLG_BASE ; 
 int VER_FLG_WEAK ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *get_ver_flags(ut32 flags) {
	static char buff[32];
	buff[0] = 0;

	if (!flags) {
		return "none";
	}
	if (flags & VER_FLG_BASE) {
		strcpy (buff, "BASE ");
	}
	if (flags & VER_FLG_WEAK) {
		if (flags & VER_FLG_BASE) {
			strcat (buff, "| ");
		}
		strcat (buff, "WEAK ");
	}

	if (flags & ~(VER_FLG_BASE | VER_FLG_WEAK)) {
		strcat (buff, "| <unknown>");
	}
	return buff;
}