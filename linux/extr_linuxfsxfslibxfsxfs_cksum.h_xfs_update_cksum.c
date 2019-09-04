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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_end_cksum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_start_cksum_update (char*,size_t,unsigned long) ; 

__attribute__((used)) static inline void
xfs_update_cksum(char *buffer, size_t length, unsigned long cksum_offset)
{
	uint32_t crc = xfs_start_cksum_update(buffer, length, cksum_offset);

	*(__le32 *)(buffer + cksum_offset) = xfs_end_cksum(crc);
}