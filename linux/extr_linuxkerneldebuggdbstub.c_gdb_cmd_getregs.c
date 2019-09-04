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
struct kgdb_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUMREGBYTES ; 
 int /*<<< orphan*/  gdb_get_regs_helper (struct kgdb_state*) ; 
 scalar_t__ gdb_regs ; 
 int /*<<< orphan*/  kgdb_mem2hex (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remcom_out_buffer ; 

__attribute__((used)) static void gdb_cmd_getregs(struct kgdb_state *ks)
{
	gdb_get_regs_helper(ks);
	kgdb_mem2hex((char *)gdb_regs, remcom_out_buffer, NUMREGBYTES);
}