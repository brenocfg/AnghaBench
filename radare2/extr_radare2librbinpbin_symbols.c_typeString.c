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
 int is64 ; 

__attribute__((used)) static const char *typeString(ut32 n, int *bits) {
	*bits = 32;
	if (n == 12) { // CPU_SUBTYPE_ARM_V7) {
		return "arm";
	}
	if (n == 0x0100000c) { // arm64
		*bits = 64;
		is64 = true;
		return "arm";
	}
	if (n == 0x0200000c) { // arm64-32
		//  TODO: must change bits
		is64 = false;
		*bits = 64;
		return "arm";
	}
	return "x86";
}