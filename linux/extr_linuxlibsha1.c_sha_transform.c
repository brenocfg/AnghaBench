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
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  T_0_15 (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  T_16_19 (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  T_20_39 (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  T_40_59 (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  T_60_79 (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void sha_transform(__u32 *digest, const char *data, __u32 *array)
{
	__u32 A, B, C, D, E;

	A = digest[0];
	B = digest[1];
	C = digest[2];
	D = digest[3];
	E = digest[4];

	/* Round 1 - iterations 0-16 take their input from 'data' */
	T_0_15( 0, A, B, C, D, E);
	T_0_15( 1, E, A, B, C, D);
	T_0_15( 2, D, E, A, B, C);
	T_0_15( 3, C, D, E, A, B);
	T_0_15( 4, B, C, D, E, A);
	T_0_15( 5, A, B, C, D, E);
	T_0_15( 6, E, A, B, C, D);
	T_0_15( 7, D, E, A, B, C);
	T_0_15( 8, C, D, E, A, B);
	T_0_15( 9, B, C, D, E, A);
	T_0_15(10, A, B, C, D, E);
	T_0_15(11, E, A, B, C, D);
	T_0_15(12, D, E, A, B, C);
	T_0_15(13, C, D, E, A, B);
	T_0_15(14, B, C, D, E, A);
	T_0_15(15, A, B, C, D, E);

	/* Round 1 - tail. Input from 512-bit mixing array */
	T_16_19(16, E, A, B, C, D);
	T_16_19(17, D, E, A, B, C);
	T_16_19(18, C, D, E, A, B);
	T_16_19(19, B, C, D, E, A);

	/* Round 2 */
	T_20_39(20, A, B, C, D, E);
	T_20_39(21, E, A, B, C, D);
	T_20_39(22, D, E, A, B, C);
	T_20_39(23, C, D, E, A, B);
	T_20_39(24, B, C, D, E, A);
	T_20_39(25, A, B, C, D, E);
	T_20_39(26, E, A, B, C, D);
	T_20_39(27, D, E, A, B, C);
	T_20_39(28, C, D, E, A, B);
	T_20_39(29, B, C, D, E, A);
	T_20_39(30, A, B, C, D, E);
	T_20_39(31, E, A, B, C, D);
	T_20_39(32, D, E, A, B, C);
	T_20_39(33, C, D, E, A, B);
	T_20_39(34, B, C, D, E, A);
	T_20_39(35, A, B, C, D, E);
	T_20_39(36, E, A, B, C, D);
	T_20_39(37, D, E, A, B, C);
	T_20_39(38, C, D, E, A, B);
	T_20_39(39, B, C, D, E, A);

	/* Round 3 */
	T_40_59(40, A, B, C, D, E);
	T_40_59(41, E, A, B, C, D);
	T_40_59(42, D, E, A, B, C);
	T_40_59(43, C, D, E, A, B);
	T_40_59(44, B, C, D, E, A);
	T_40_59(45, A, B, C, D, E);
	T_40_59(46, E, A, B, C, D);
	T_40_59(47, D, E, A, B, C);
	T_40_59(48, C, D, E, A, B);
	T_40_59(49, B, C, D, E, A);
	T_40_59(50, A, B, C, D, E);
	T_40_59(51, E, A, B, C, D);
	T_40_59(52, D, E, A, B, C);
	T_40_59(53, C, D, E, A, B);
	T_40_59(54, B, C, D, E, A);
	T_40_59(55, A, B, C, D, E);
	T_40_59(56, E, A, B, C, D);
	T_40_59(57, D, E, A, B, C);
	T_40_59(58, C, D, E, A, B);
	T_40_59(59, B, C, D, E, A);

	/* Round 4 */
	T_60_79(60, A, B, C, D, E);
	T_60_79(61, E, A, B, C, D);
	T_60_79(62, D, E, A, B, C);
	T_60_79(63, C, D, E, A, B);
	T_60_79(64, B, C, D, E, A);
	T_60_79(65, A, B, C, D, E);
	T_60_79(66, E, A, B, C, D);
	T_60_79(67, D, E, A, B, C);
	T_60_79(68, C, D, E, A, B);
	T_60_79(69, B, C, D, E, A);
	T_60_79(70, A, B, C, D, E);
	T_60_79(71, E, A, B, C, D);
	T_60_79(72, D, E, A, B, C);
	T_60_79(73, C, D, E, A, B);
	T_60_79(74, B, C, D, E, A);
	T_60_79(75, A, B, C, D, E);
	T_60_79(76, E, A, B, C, D);
	T_60_79(77, D, E, A, B, C);
	T_60_79(78, C, D, E, A, B);
	T_60_79(79, B, C, D, E, A);

	digest[0] += A;
	digest[1] += B;
	digest[2] += C;
	digest[3] += D;
	digest[4] += E;
}