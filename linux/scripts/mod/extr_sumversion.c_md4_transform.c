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
 int /*<<< orphan*/  ROUND1 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__ const,int) ; 
 int /*<<< orphan*/  ROUND2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__ const,int) ; 
 int /*<<< orphan*/  ROUND3 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__ const,int) ; 

__attribute__((used)) static void md4_transform(uint32_t *hash, uint32_t const *in)
{
	uint32_t a, b, c, d;

	a = hash[0];
	b = hash[1];
	c = hash[2];
	d = hash[3];

	ROUND1(a, b, c, d, in[0], 3);
	ROUND1(d, a, b, c, in[1], 7);
	ROUND1(c, d, a, b, in[2], 11);
	ROUND1(b, c, d, a, in[3], 19);
	ROUND1(a, b, c, d, in[4], 3);
	ROUND1(d, a, b, c, in[5], 7);
	ROUND1(c, d, a, b, in[6], 11);
	ROUND1(b, c, d, a, in[7], 19);
	ROUND1(a, b, c, d, in[8], 3);
	ROUND1(d, a, b, c, in[9], 7);
	ROUND1(c, d, a, b, in[10], 11);
	ROUND1(b, c, d, a, in[11], 19);
	ROUND1(a, b, c, d, in[12], 3);
	ROUND1(d, a, b, c, in[13], 7);
	ROUND1(c, d, a, b, in[14], 11);
	ROUND1(b, c, d, a, in[15], 19);

	ROUND2(a, b, c, d,in[ 0], 3);
	ROUND2(d, a, b, c, in[4], 5);
	ROUND2(c, d, a, b, in[8], 9);
	ROUND2(b, c, d, a, in[12], 13);
	ROUND2(a, b, c, d, in[1], 3);
	ROUND2(d, a, b, c, in[5], 5);
	ROUND2(c, d, a, b, in[9], 9);
	ROUND2(b, c, d, a, in[13], 13);
	ROUND2(a, b, c, d, in[2], 3);
	ROUND2(d, a, b, c, in[6], 5);
	ROUND2(c, d, a, b, in[10], 9);
	ROUND2(b, c, d, a, in[14], 13);
	ROUND2(a, b, c, d, in[3], 3);
	ROUND2(d, a, b, c, in[7], 5);
	ROUND2(c, d, a, b, in[11], 9);
	ROUND2(b, c, d, a, in[15], 13);

	ROUND3(a, b, c, d,in[ 0], 3);
	ROUND3(d, a, b, c, in[8], 9);
	ROUND3(c, d, a, b, in[4], 11);
	ROUND3(b, c, d, a, in[12], 15);
	ROUND3(a, b, c, d, in[2], 3);
	ROUND3(d, a, b, c, in[10], 9);
	ROUND3(c, d, a, b, in[6], 11);
	ROUND3(b, c, d, a, in[14], 15);
	ROUND3(a, b, c, d, in[1], 3);
	ROUND3(d, a, b, c, in[9], 9);
	ROUND3(c, d, a, b, in[5], 11);
	ROUND3(b, c, d, a, in[13], 15);
	ROUND3(a, b, c, d, in[3], 3);
	ROUND3(d, a, b, c, in[11], 9);
	ROUND3(c, d, a, b, in[7], 11);
	ROUND3(b, c, d, a, in[15], 15);

	hash[0] += a;
	hash[1] += b;
	hash[2] += c;
	hash[3] += d;
}