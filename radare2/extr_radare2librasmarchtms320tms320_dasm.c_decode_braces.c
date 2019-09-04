#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* syntax; } ;
typedef  TYPE_1__ tms320_dasm_t ;

/* Variables and functions */
 int /*<<< orphan*/  R ; 
 scalar_t__ field_valid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int field_value (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace (char*,char*,char*,...) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  substitute (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  u ; 
 int /*<<< orphan*/  uu ; 

void decode_braces(tms320_dasm_t * dasm)
{
	char * pos;

	pos = strstr(dasm->syntax, "[(saturate]");
	if (pos) {
		replace(pos, "[)", ")[");
		replace(dasm->syntax, "[(saturate]", "%s", "(saturate");
	}

	if (field_valid(dasm, R)) {
		pos = strstr(dasm->syntax, "[rnd(]");
		if (pos) {
			replace(pos, "[)", "%s", field_value(dasm, R) ? ")[" : "[");
			replace(dasm->syntax, "[rnd(]", "%s", field_value(dasm, R) ? "rnd(" : "");
		}
	}

	if (field_valid(dasm, u)) {
		pos = strstr(dasm->syntax, "[uns(]");
		if (pos) {
			replace(pos, "[)", "%s", field_value(dasm, u) ? ")[" : "[");
			replace(dasm->syntax, "[uns(]", "%s", field_value(dasm, u) ? "uns(" : "");
		}
	}

	if (field_valid(dasm, uu)) {
		bool parallel = !!strstr (dasm->syntax, "::");

		// first
		replace(dasm->syntax, "[uns(]", "%s", field_value(dasm, uu) & 2 ? "uns(" : "");
		replace(dasm->syntax, "[)]", "%s", field_value(dasm, uu) & 2 ? ")" : "");

		if (parallel) {
			replace(dasm->syntax, "[uns(]", "%s", field_value(dasm, uu) & 2 ? "uns(" : "");
			replace(dasm->syntax, "[)]", "%s", field_value(dasm, uu) & 2 ? ")" : "");
		}

		// second
		replace(dasm->syntax, "[uns(]", "%s", field_value(dasm, uu) & 1 ? "uns(" : "");
		replace(dasm->syntax, "[)]", "%s", field_value(dasm, uu) & 1 ? ")" : "");

		if (parallel) {
			replace(dasm->syntax, "[uns(]", "%s", field_value(dasm, uu) & 1 ? "uns(" : "");
			replace(dasm->syntax, "[)]", "%s", field_value(dasm, uu) & 1 ? ")" : "");
		}
	}

	// remove rudiments

	substitute(dasm->syntax, "[]", "%s", "");
}