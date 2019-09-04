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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_CRC_SEED ; 
 int /*<<< orphan*/  crc32c (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static inline uint32_t
xfs_start_cksum_update(char *buffer, size_t length, unsigned long cksum_offset)
{
	/* zero the CRC field */
	*(__le32 *)(buffer + cksum_offset) = 0;

	/* single pass CRC calculation for the entire buffer */
	return crc32c(XFS_CRC_SEED, buffer, length);
}