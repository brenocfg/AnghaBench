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
typedef  scalar_t__ lzma_ret ;

/* Variables and functions */
#define  LZMA_BUF_ERROR 132 
#define  LZMA_DATA_ERROR 131 
#define  LZMA_FORMAT_ERROR 130 
#define  LZMA_MEM_ERROR 129 
#define  LZMA_OPTIONS_ERROR 128 

__attribute__((used)) static const char *lzma_strerror(lzma_ret ret)
{
	switch ((int) ret) {
	case LZMA_MEM_ERROR:
		return "Memory allocation failed";
	case LZMA_OPTIONS_ERROR:
		return "Unsupported decompressor flags";
	case LZMA_FORMAT_ERROR:
		return "The input is not in the .xz format";
	case LZMA_DATA_ERROR:
		return "Compressed file is corrupt";
	case LZMA_BUF_ERROR:
		return "Compressed file is truncated or otherwise corrupt";
	default:
		return "Unknown error, possibly a bug";
	}
}