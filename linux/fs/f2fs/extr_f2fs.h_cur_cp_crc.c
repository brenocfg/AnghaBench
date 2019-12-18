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
struct f2fs_checkpoint {int /*<<< orphan*/  checksum_offset; } ;
typedef  size_t __u64 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __u64 cur_cp_crc(struct f2fs_checkpoint *cp)
{
	size_t crc_offset = le32_to_cpu(cp->checksum_offset);
	return le32_to_cpu(*((__le32 *)((unsigned char *)cp + crc_offset)));
}