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
 scalar_t__ is_indirect_reg (char const*) ; 
 scalar_t__ is_reg (char const*) ; 

__attribute__((used)) static int register_number(char const*reg) {
	if (is_reg (reg)) {
		return reg[1] - '0';
	}
	if (is_indirect_reg (reg)) {
		return reg[2] - '0';
	}
	return 8; // not register 0-7, so...
}