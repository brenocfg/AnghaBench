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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  Decode (scalar_t__*,unsigned char const*,int) ; 
 int /*<<< orphan*/  MD4_R1 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  MD4_R2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  MD4_R3 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int) ; 

__attribute__((used)) static void MD4Transform(uint32_t state[4], const unsigned char block[64])
{
	uint32_t a = state[0], b = state[1], c = state[2], d = state[3], x[16];

	Decode(x, block, 64);

	/* Round 1 */
	MD4_R1(a,b,c,d, 0, 3);
	MD4_R1(d,a,b,c, 1, 7);
	MD4_R1(c,d,a,b, 2,11);
	MD4_R1(b,c,d,a, 3,19);
	MD4_R1(a,b,c,d, 4, 3);
	MD4_R1(d,a,b,c, 5, 7);
	MD4_R1(c,d,a,b, 6,11);
	MD4_R1(b,c,d,a, 7,19);
	MD4_R1(a,b,c,d, 8, 3);
	MD4_R1(d,a,b,c, 9, 7);
	MD4_R1(c,d,a,b,10,11);
	MD4_R1(b,c,d,a,11,19);
	MD4_R1(a,b,c,d,12, 3);
	MD4_R1(d,a,b,c,13, 7);
	MD4_R1(c,d,a,b,14,11);
	MD4_R1(b,c,d,a,15,19);

	/* Round 2 */
	MD4_R2(a,b,c,d, 0, 3);
	MD4_R2(d,a,b,c, 4, 5);
	MD4_R2(c,d,a,b, 8, 9);
	MD4_R2(b,c,d,a,12,13);
	MD4_R2(a,b,c,d, 1, 3);
	MD4_R2(d,a,b,c, 5, 5);
	MD4_R2(c,d,a,b, 9, 9);
	MD4_R2(b,c,d,a,13,13);
	MD4_R2(a,b,c,d, 2, 3);
	MD4_R2(d,a,b,c, 6, 5);
	MD4_R2(c,d,a,b,10, 9);
	MD4_R2(b,c,d,a,14,13);
	MD4_R2(a,b,c,d, 3, 3);
	MD4_R2(d,a,b,c, 7, 5);
	MD4_R2(c,d,a,b,11, 9);
	MD4_R2(b,c,d,a,15,13);

	/* Round 3 */
	MD4_R3(a,b,c,d, 0, 3);
	MD4_R3(d,a,b,c, 8, 9);
	MD4_R3(c,d,a,b, 4,11);
	MD4_R3(b,c,d,a,12,15);
	MD4_R3(a,b,c,d, 2, 3);
	MD4_R3(d,a,b,c,10, 9);
	MD4_R3(c,d,a,b, 6,11);
	MD4_R3(b,c,d,a,14,15);
	MD4_R3(a,b,c,d, 1, 3);
	MD4_R3(d,a,b,c, 9, 9);
	MD4_R3(c,d,a,b, 5,11);
	MD4_R3(b,c,d,a,13,15);
	MD4_R3(a,b,c,d, 3, 3);
	MD4_R3(d,a,b,c,11, 9);
	MD4_R3(c,d,a,b, 7,11);
	MD4_R3(b,c,d,a,15,15);

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}