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
typedef  int ut64 ;
typedef  int ut32 ;

/* Variables and functions */
 int UT32_MAX ; 
 int countLeadingOnes (int) ; 
 int countTrailingOnes (int) ; 
 int countTrailingZeros (int) ; 
 scalar_t__ isShiftedMask (int) ; 

__attribute__((used)) static ut32 decodeBitMasks(ut32 imm) {
	// get element size
	int size = 32;
	// determine rot to make element be 0^m 1^n
	ut32 cto, i;
	ut32 mask = ((ut64) - 1LL) >> (64 - size);

	if (isShiftedMask (imm)) {
		i = countTrailingZeros (imm);
		cto = countTrailingOnes (imm >> i);
	} else {
		imm |= ~mask;
		if (!isShiftedMask (imm)) {
			return UT32_MAX;
		}

		ut32 clo = countLeadingOnes (imm);
		i = 64 - clo;
		cto = clo + countTrailingOnes (imm) - (64 - size);
	}

	// Encode in Immr the number of RORs it would take to get *from* 0^m 1^n
	// to our target value, where I is the number of RORs to go the opposite
	// direction
	ut32 immr = (size - i) & (size - 1);
	// If size has a 1 in the n'th bit, create a value that has zeroes in
	// bits [0, n] and ones above that.
	ut64 nimms = ~(size - 1) << 1;
	// Or the cto value into the low bits, which must be below the Nth bit
	// bit mentioned above.
	nimms |= (cto - 1);
	// Extract and toggle seventh bit to make N field.
	ut32 n = ((nimms >> 6) & 1) ^ 1;
	ut64 encoding = (n << 12) | (immr << 6) | (nimms & 0x3f);
	return encoding;
}