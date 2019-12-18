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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  amd29k_instr_t ;

/* Variables and functions */
 scalar_t__ AMD29K_HAS_BIT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AMD29K_SET_INVALID (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AMD29K_SET_VALUE (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMD29K_TYPE_IMM ; 
 int /*<<< orphan*/  AMD29K_TYPE_REG ; 

__attribute__((used)) static void decode_ra_rb_rci(amd29k_instr_t* instruction, const ut8* buffer) {
	AMD29K_SET_VALUE (instruction, 0, buffer[1], AMD29K_TYPE_REG);
	AMD29K_SET_VALUE (instruction, 1, buffer[2], AMD29K_TYPE_REG);
	if (AMD29K_HAS_BIT (buffer)) {
		AMD29K_SET_VALUE (instruction, 2, buffer[3], AMD29K_TYPE_IMM);
	} else {
		AMD29K_SET_VALUE (instruction, 2, buffer[3], AMD29K_TYPE_REG);
	}
	AMD29K_SET_INVALID (instruction, 3);
	AMD29K_SET_INVALID (instruction, 4);
	AMD29K_SET_INVALID (instruction, 5);
}