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
typedef  int /*<<< orphan*/  pg_crc32 ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_TRADITIONAL_CRC32 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  FIN_TRADITIONAL_CRC32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_TRADITIONAL_CRC32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static pg_crc32
crc32_sz(char *buf, int size)
{
	pg_crc32	crc;

	INIT_TRADITIONAL_CRC32(crc);
	COMP_TRADITIONAL_CRC32(crc, buf, size);
	FIN_TRADITIONAL_CRC32(crc);

	return crc;
}