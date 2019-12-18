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
 unsigned int EXT4_MAX_REC_LEN ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int
ext4_rec_len_from_disk(__le16 dlen, unsigned blocksize)
{
	unsigned len = le16_to_cpu(dlen);

#if (PAGE_SIZE >= 65536)
	if (len == EXT4_MAX_REC_LEN || len == 0)
		return blocksize;
	return (len & 65532) | ((len & 3) << 16);
#else
	return len;
#endif
}