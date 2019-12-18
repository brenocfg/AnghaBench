#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* assembler; } ;
struct TYPE_6__ {TYPE_1__* cur; } ;
struct TYPE_5__ {char* arch; } ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 char* strstr (char*,char*) ; 

__attribute__((used)) static void _handle_call(RCore *core, char *line, char **str) {
	if (!core || !core->assembler || !core->assembler->cur) {
		*str = NULL;
		return;
	}
	if (strstr (core->assembler->cur->arch, "x86")) {
		*str = strstr (line, "call ");
	} else if (strstr (core->assembler->cur->arch, "arm")) {
		*str = strstr (line, " b ");
		if (*str && strstr (*str, " 0x")) {
			/*
			* avoid treating branches to
			* non-symbols as calls
			*/
			*str = NULL;
		}
		if (!*str) {
			*str = strstr (line, "bl ");
		}
		if (!*str) {
			*str = strstr (line, "bx ");
		}
	}
}