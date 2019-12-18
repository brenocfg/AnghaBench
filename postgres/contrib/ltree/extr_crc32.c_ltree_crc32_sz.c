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
typedef  scalar_t__ pg_crc32 ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_TRADITIONAL_CRC32 (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  FIN_TRADITIONAL_CRC32 (scalar_t__) ; 
 int /*<<< orphan*/  INIT_TRADITIONAL_CRC32 (scalar_t__) ; 
 scalar_t__ TOLOWER (char) ; 

unsigned int
ltree_crc32_sz(char *buf, int size)
{
	pg_crc32	crc;
	char	   *p = buf;

	INIT_TRADITIONAL_CRC32(crc);
	while (size > 0)
	{
		char		c = (char) TOLOWER(*p);

		COMP_TRADITIONAL_CRC32(crc, &c, 1);
		size--;
		p++;
	}
	FIN_TRADITIONAL_CRC32(crc);
	return (unsigned int) crc;
}