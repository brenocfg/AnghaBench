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
 int /*<<< orphan*/  BUG () ; 
 unsigned int EXT4_MAX_REC_LEN ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 

__attribute__((used)) static inline __le16 ext4_rec_len_to_disk(unsigned len, unsigned blocksize)
{
	if ((len > blocksize) || (blocksize > (1 << 18)) || (len & 3))
		BUG();
#if (PAGE_SIZE >= 65536)
	if (len < 65536)
		return cpu_to_le16(len);
	if (len == blocksize) {
		if (blocksize == 65536)
			return cpu_to_le16(EXT4_MAX_REC_LEN);
		else
			return cpu_to_le16(0);
	}
	return cpu_to_le16((len & 65532) | ((len >> 16) & 3));
#else
	return cpu_to_le16(len);
#endif
}