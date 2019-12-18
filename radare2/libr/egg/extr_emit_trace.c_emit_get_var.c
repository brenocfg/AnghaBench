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
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void emit_get_var (REgg *egg, int type, char *out, int idx) {
	switch (type) {
	case 0: sprintf (out, "fp,$%d", -idx); break; /* variable */
	case 1: sprintf (out, "sp,$%d", idx); break; /* argument */ // XXX: MUST BE r0, r1, r2, ..
	}
}