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
typedef  int /*<<< orphan*/  REgg ;

/* Variables and functions */
 scalar_t__ R_REG_AR_OFF ; 
 char* emit_regs (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static void emit_get_ar (REgg *egg, char *out, int idx) {
	const char *reg = emit_regs (egg, R_REG_AR_OFF + idx);

	if (reg) {
		strcpy (out, reg);
	}
}