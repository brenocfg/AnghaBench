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
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static bool handlePAC(ut32 *op, const char *str) {
	if (!strcmp (str, "autiasp")) {
		*op = 0xbf2303d5;
		return true;
	}
	if (!strcmp (str, "autiaz")) {
		*op = 0x9f2303d5;
		return true;
	}
	if (!strcmp (str, "autibsp")) {
		*op = 0xff2303d5;
		return true;
	}
	if (!strcmp (str, "autibz")) {
		*op = 0xdf2303d5;
		return true;
	}
	if (!strcmp (str, "paciaz")) {
		*op = 0x1f2303d5;
		return true;
	}
	if (!strcmp (str, "pacibz")) {
		*op = 0x5f2303d5;
		return true;
	}
	if (!strcmp (str, "paciasp")) {
		*op = 0x3f2303d5;
		return true;
	}
	if (!strcmp (str, "pacibsp")) {
		*op = 0x7f2303d5;
		return true;
	}
	if (!strcmp (str, "retab")) {
		*op = 0xff0f5fd6;
		return true;
	}
	return false;
}