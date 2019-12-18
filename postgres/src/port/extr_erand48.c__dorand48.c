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
typedef  int uint64 ;

/* Variables and functions */
 int RAND48_ADD ; 
 int RAND48_MULT ; 

__attribute__((used)) static uint64
_dorand48(unsigned short xseed[3])
{
	/*
	 * We do the arithmetic in uint64; any type wider than 48 bits would work.
	 */
	uint64		in;
	uint64		out;

	in = (uint64) xseed[2] << 32 | (uint64) xseed[1] << 16 | (uint64) xseed[0];

	out = in * RAND48_MULT + RAND48_ADD;

	xseed[0] = out & 0xFFFF;
	xseed[1] = (out >> 16) & 0xFFFF;
	xseed[2] = (out >> 32) & 0xFFFF;

	return out;
}