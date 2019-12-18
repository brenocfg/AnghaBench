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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ph (int*) ; 
 int /*<<< orphan*/  round (int,int,int,int const*) ; 
 int** tables ; 

__attribute__((used)) static inline void Snefru(uint32_t input[16])
{
	static int shifts[4] = {16, 8, 16, 24};
	int b, index, rshift, lshift;
	const uint32_t *t0,*t1;
	uint32_t SBE,B00,B01,B02,B03,B04,B05,B06,B07,B08,B09,B10,B11,B12,B13,B14,B15;

	B00 = input[0];
	B01 = input[1];
	B02 = input[2];
	B03 = input[3];
	B04 = input[4];
	B05 = input[5];
	B06 = input[6];
	B07 = input[7];
	B08 = input[8];
	B09 = input[9];
	B10 = input[10];
	B11 = input[11];
	B12 = input[12];
	B13 = input[13];
	B14 = input[14];
	B15 = input[15];

	for (index = 0; index < 8; index++) {
		t0 = tables[2*index+0];
		t1 = tables[2*index+1];
		for (b = 0; b < 4; b++) {
			round(B15, B00, B01, t0);
			round(B00, B01, B02, t0);
			round(B01, B02, B03, t1);
			round(B02, B03, B04, t1);
			round(B03, B04, B05, t0);
			round(B04, B05, B06, t0);
			round(B05, B06, B07, t1);
			round(B06, B07, B08, t1);
			round(B07, B08, B09, t0);
			round(B08, B09, B10, t0);
			round(B09, B10, B11, t1);
			round(B10, B11, B12, t1);
			round(B11, B12, B13, t0);
			round(B12, B13, B14, t0);
			round(B13, B14, B15, t1);
			round(B14, B15, B00, t1);

			rshift = shifts[b];
			lshift = 32-rshift;

			B00 = (B00 >> rshift) | (B00 << lshift);
			B01 = (B01 >> rshift) | (B01 << lshift);
			B02 = (B02 >> rshift) | (B02 << lshift);
			B03 = (B03 >> rshift) | (B03 << lshift);
			B04 = (B04 >> rshift) | (B04 << lshift);
			B05 = (B05 >> rshift) | (B05 << lshift);
			B06 = (B06 >> rshift) | (B06 << lshift);
			B07 = (B07 >> rshift) | (B07 << lshift);
			B08 = (B08 >> rshift) | (B08 << lshift);
			B09 = (B09 >> rshift) | (B09 << lshift);
			B10 = (B10 >> rshift) | (B10 << lshift);
			B11 = (B11 >> rshift) | (B11 << lshift);
			B12 = (B12 >> rshift) | (B12 << lshift);
			B13 = (B13 >> rshift) | (B13 << lshift);
			B14 = (B14 >> rshift) | (B14 << lshift);
			B15 = (B15 >> rshift) | (B15 << lshift);
		}
	}
	input[0] ^= B15;
	input[1] ^= B14;
	input[2] ^= B13;
	input[3] ^= B12;
	input[4] ^= B11;
	input[5] ^= B10;
	input[6] ^= B09;
	input[7] ^= B08;
#if DBG_SNEFRU
	ph(input);
#endif
}