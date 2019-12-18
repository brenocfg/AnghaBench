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
 int /*<<< orphan*/  strcmpnull (char*,char*) ; 

__attribute__((used)) static char *parse_hints(char *input) {
	if (!strcmpnull (input, "unst")) {
		return "6";
	}
	if (!strcmpnull (input, "un")) {
		return "7";
	}
	if (!strcmpnull (input, "st")) {
		return "14";
	}
	if (!strcmpnull (input, "sy")) {
		return "15";
	}
	return "-1";
}