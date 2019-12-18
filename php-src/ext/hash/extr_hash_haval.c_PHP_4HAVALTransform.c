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
typedef  int /*<<< orphan*/  x ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  Decode (scalar_t__*,unsigned char const*,int) ; 
 scalar_t__ F1 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ F2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ F3 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ F4 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 size_t* I2 ; 
 size_t* I3 ; 
 size_t* I4 ; 
 scalar_t__* K2 ; 
 scalar_t__* K3 ; 
 scalar_t__* K4 ; 
 size_t* M0 ; 
 size_t* M1 ; 
 size_t* M2 ; 
 size_t* M3 ; 
 size_t* M4 ; 
 size_t* M5 ; 
 size_t* M6 ; 
 size_t* M7 ; 
 scalar_t__ ROTR (scalar_t__,int) ; 
 int /*<<< orphan*/  ZEND_SECURE_ZERO (unsigned char*,int) ; 

__attribute__((used)) static void PHP_4HAVALTransform(uint32_t state[8], const unsigned char block[128])
{
	uint32_t E[8];
	uint32_t x[32];
	int i;

	Decode(x, block, 128);

	for(i = 0; i < 8; i++) {
		E[i] = state[i];
	}

	for(i = 0; i < 32; i++) {
		E[7 - (i % 8)] = ROTR(F1(E[M2[i]],E[M6[i]],E[M1[i]],E[M4[i]],E[M5[i]],E[M3[i]],E[M0[i]]),7) + ROTR(E[M7[i]],11) + x[i];
	}
	for(i = 0; i < 32; i++) {
		E[7 - (i % 8)] = ROTR(F2(E[M3[i]],E[M5[i]],E[M2[i]],E[M0[i]],E[M1[i]],E[M6[i]],E[M4[i]]),7) + ROTR(E[M7[i]],11) + x[I2[i]] + K2[i];
	}
	for(i = 0; i < 32; i++) {
		E[7 - (i % 8)] = ROTR(F3(E[M1[i]],E[M4[i]],E[M3[i]],E[M6[i]],E[M0[i]],E[M2[i]],E[M5[i]]),7) + ROTR(E[M7[i]],11) + x[I3[i]] + K3[i];
	}
	for(i = 0; i < 32; i++) {
		E[7 - (i % 8)] = ROTR(F4(E[M6[i]],E[M4[i]],E[M0[i]],E[M5[i]],E[M2[i]],E[M1[i]],E[M3[i]]),7) + ROTR(E[M7[i]],11) + x[I4[i]] + K4[i];
	}

	/* Update digest */
	for(i = 0; i < 8; i++) {
		state[i] += E[i];
	}

	/* Zeroize sensitive information. */
	ZEND_SECURE_ZERO((unsigned char*) x, sizeof(x));
}