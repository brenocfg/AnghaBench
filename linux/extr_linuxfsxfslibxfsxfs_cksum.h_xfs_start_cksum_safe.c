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
typedef  char uint32_t ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 char XFS_CRC_SEED ; 
 char crc32c (char,char*,size_t) ; 

__attribute__((used)) static inline uint32_t
xfs_start_cksum_safe(char *buffer, size_t length, unsigned long cksum_offset)
{
	uint32_t zero = 0;
	uint32_t crc;

	/* Calculate CRC up to the checksum. */
	crc = crc32c(XFS_CRC_SEED, buffer, cksum_offset);

	/* Skip checksum field */
	crc = crc32c(crc, &zero, sizeof(__u32));

	/* Calculate the rest of the CRC. */
	return crc32c(crc, &buffer[cksum_offset + sizeof(__be32)],
		      length - (cksum_offset + sizeof(__be32)));
}