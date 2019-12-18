#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* assembler; int /*<<< orphan*/  config; } ;
struct TYPE_9__ {int bits; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_dbg_map_heap_glibc_32 (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  cmd_dbg_map_heap_glibc_64 (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  cmd_dbg_map_jemalloc_32 (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  cmd_dbg_map_jemalloc_64 (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  cmd_debug_map_heap_win (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static int r_debug_heap(RCore *core, const char *input) {
	const char *m = r_config_get (core->config, "dbg.malloc");
	if (m && !strcmp ("glibc", m)) {
#if __linux__ && __GNU_LIBRARY__ && __GLIBC__ && __GLIBC_MINOR__
		if (core->assembler->bits == 64) {
			cmd_dbg_map_heap_glibc_64 (core, input + 1);
		} else {
			cmd_dbg_map_heap_glibc_32 (core, input + 1);
		}
#else
		eprintf ("glibc not supported for this platform\n");
#endif
#if HAVE_JEMALLOC
	} else if (m && !strcmp ("jemalloc", m)) {
		if (core->assembler->bits == 64) {
			cmd_dbg_map_jemalloc_64 (core, input + 1);
		} else {
			cmd_dbg_map_jemalloc_32 (core, input + 1);
		}
#endif
	} else {
#if __WINDOWS__
		cmd_debug_map_heap_win (core, input + 1);
#else
		eprintf ("MALLOC algorithm not supported\n");
		return false;
#endif
	}
	return true;
}