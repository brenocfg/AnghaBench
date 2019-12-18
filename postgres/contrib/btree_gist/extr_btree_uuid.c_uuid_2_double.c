#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ pg_uuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  UUID_LEN ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_bswap64 (scalar_t__) ; 

__attribute__((used)) static double
uuid_2_double(const pg_uuid_t *u)
{
	uint64		uu[2];
	const double two64 = 18446744073709551616.0;	/* 2^64 */

	/* Source data may not be suitably aligned, so copy */
	memcpy(uu, u->data, UUID_LEN);

	/*
	 * uuid values should be considered as big-endian numbers, since that
	 * corresponds to how memcmp will compare them.  On a little-endian
	 * machine, byte-swap each half so we can use native uint64 arithmetic.
	 */
#ifndef WORDS_BIGENDIAN
	uu[0] = pg_bswap64(uu[0]);
	uu[1] = pg_bswap64(uu[1]);
#endif

	/*
	 * 2^128 is about 3.4e38, which in theory could exceed the range of
	 * "double" (POSIX only requires 1e37).  To avoid any risk of overflow,
	 * put the decimal point between the two halves rather than treating the
	 * uuid value as a 128-bit integer.
	 */
	return (double) uu[0] + (double) uu[1] / two64;
}