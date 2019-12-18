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
typedef  int /*<<< orphan*/  trgm ;
typedef  char pg_crc32 ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_LEGACY_CRC32 (char,char*,int) ; 
 int /*<<< orphan*/  CPTRGM (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FIN_LEGACY_CRC32 (char) ; 
 int /*<<< orphan*/  INIT_LEGACY_CRC32 (char) ; 

void
compact_trigram(trgm *tptr, char *str, int bytelen)
{
	if (bytelen == 3)
	{
		CPTRGM(tptr, str);
	}
	else
	{
		pg_crc32	crc;

		INIT_LEGACY_CRC32(crc);
		COMP_LEGACY_CRC32(crc, str, bytelen);
		FIN_LEGACY_CRC32(crc);

		/*
		 * use only 3 upper bytes from crc, hope, it's good enough hashing
		 */
		CPTRGM(tptr, &crc);
	}
}