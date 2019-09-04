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
 int /*<<< orphan*/  CRC32C_POLY_LE ; 
 int /*<<< orphan*/  crc32ctable_le ; 
 int /*<<< orphan*/  crc32init_le_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crc32cinit_le(void)
{
	crc32init_le_generic(CRC32C_POLY_LE, crc32ctable_le);
}