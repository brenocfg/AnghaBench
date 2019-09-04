#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bits; void* arch; } ;
struct TYPE_5__ {TYPE_1__ target; } ;
typedef  TYPE_2__ libgdbr_t ;

/* Variables and functions */
 void* R_SYS_ARCH_ARM ; 
 void* R_SYS_ARCH_MIPS ; 
 void* R_SYS_ARCH_NONE ; 
 void* R_SYS_ARCH_X86 ; 
 int /*<<< orphan*/  eprintf (char*,char*) ; 
 scalar_t__ r_str_startswith (char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int _resolve_arch(libgdbr_t *g, char *xml_data) {
	char *arch;
	// Find architecture
	g->target.arch = R_SYS_ARCH_NONE;
	if ((arch = strstr (xml_data, "<architecture"))) {
		if (!(arch = strchr (arch, '>'))) {
			return -1;
		}
		arch++;
		if (r_str_startswith (arch, "i386")) {
			g->target.arch = R_SYS_ARCH_X86;
			g->target.bits = 32;
			arch += 4;
			if (r_str_startswith (arch, ":x86-64")) {
				g->target.bits = 64;
			}
		} else if (r_str_startswith (arch, "aarch64")) {
			g->target.arch = R_SYS_ARCH_ARM;
			g->target.bits = 64;
		} else if (r_str_startswith (arch, "arm")) {
			g->target.arch = R_SYS_ARCH_ARM;
			g->target.bits = 32;
		} else if (r_str_startswith (arch, "mips")) {
			g->target.arch = R_SYS_ARCH_MIPS;
			g->target.bits = 32;
		}
		// TODO others
	} else {
		// apple's debugserver on ios9
		if (strstr (xml_data, "com.apple.debugserver.arm64")) {
			g->target.arch = R_SYS_ARCH_ARM;
			g->target.bits = 64;
		} else if (strstr (xml_data, "org.gnu.gdb.mips")) {
			// openocd mips?
			g->target.arch = R_SYS_ARCH_MIPS;
			g->target.bits = 32;
		} else if (strstr(xml_data, "com.apple.debugserver.x86_64")) {
			g->target.arch = R_SYS_ARCH_X86;
			g->target.bits = 64;
		} else {
			eprintf ("Unknown architecture parsing XML (%s)\n", xml_data);
		}
	}
	return 0;
}