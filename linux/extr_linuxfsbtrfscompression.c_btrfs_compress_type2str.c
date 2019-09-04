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
typedef  enum btrfs_compression_type { ____Placeholder_btrfs_compression_type } btrfs_compression_type ;

/* Variables and functions */
#define  BTRFS_COMPRESS_LZO 131 
#define  BTRFS_COMPRESS_NONE 130 
#define  BTRFS_COMPRESS_ZLIB 129 
#define  BTRFS_COMPRESS_ZSTD 128 
 char const** btrfs_compress_types ; 

const char* btrfs_compress_type2str(enum btrfs_compression_type type)
{
	switch (type) {
	case BTRFS_COMPRESS_ZLIB:
	case BTRFS_COMPRESS_LZO:
	case BTRFS_COMPRESS_ZSTD:
	case BTRFS_COMPRESS_NONE:
		return btrfs_compress_types[type];
	}

	return NULL;
}