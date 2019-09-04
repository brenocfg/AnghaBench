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
 int /*<<< orphan*/  CHECK_ENC_GET (int,int,int,int) ; 
 int /*<<< orphan*/  CHECK_ENC_GET_U (int,int,int,int) ; 

__attribute__((used)) static int test_constants(void)
{
	/*
	 * NOTE
	 * This whole function compiles (or at least should, if everything
	 * is going according to plan) to nothing after optimisation.
	 */

	CHECK_ENC_GET(16,  1, 0x000f, 0x0001);
	CHECK_ENC_GET(16,  3, 0x00f0, 0x0030);
	CHECK_ENC_GET(16,  5, 0x0f00, 0x0500);
	CHECK_ENC_GET(16,  7, 0xf000, 0x7000);
	CHECK_ENC_GET(16, 14, 0x000f, 0x000e);
	CHECK_ENC_GET(16, 15, 0x00f0, 0x00f0);

	CHECK_ENC_GET_U(8,  1, 0x0f, 0x01);
	CHECK_ENC_GET_U(8,  3, 0xf0, 0x30);
	CHECK_ENC_GET_U(8, 14, 0x0f, 0x0e);
	CHECK_ENC_GET_U(8, 15, 0xf0, 0xf0);

	CHECK_ENC_GET(32,  1, 0x00000f00, 0x00000100);
	CHECK_ENC_GET(32,  3, 0x0000f000, 0x00003000);
	CHECK_ENC_GET(32,  5, 0x000f0000, 0x00050000);
	CHECK_ENC_GET(32,  7, 0x00f00000, 0x00700000);
	CHECK_ENC_GET(32, 14, 0x0f000000, 0x0e000000);
	CHECK_ENC_GET(32, 15, 0xf0000000, 0xf0000000);

	CHECK_ENC_GET(64,  1, 0x00000f0000000000ull, 0x0000010000000000ull);
	CHECK_ENC_GET(64,  3, 0x0000f00000000000ull, 0x0000300000000000ull);
	CHECK_ENC_GET(64,  5, 0x000f000000000000ull, 0x0005000000000000ull);
	CHECK_ENC_GET(64,  7, 0x00f0000000000000ull, 0x0070000000000000ull);
	CHECK_ENC_GET(64, 14, 0x0f00000000000000ull, 0x0e00000000000000ull);
	CHECK_ENC_GET(64, 15, 0xf000000000000000ull, 0xf000000000000000ull);

	return 0;
}