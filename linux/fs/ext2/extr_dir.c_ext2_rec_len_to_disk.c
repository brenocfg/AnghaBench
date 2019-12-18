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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int EXT2_MAX_REC_LEN ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 

__attribute__((used)) static inline __le16 ext2_rec_len_to_disk(unsigned len)
{
#if (PAGE_SIZE >= 65536)
	if (len == (1 << 16))
		return cpu_to_le16(EXT2_MAX_REC_LEN);
	else
		BUG_ON(len > (1 << 16));
#endif
	return cpu_to_le16(len);
}