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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int LZ4_decompress_generic (char const*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  decode_full_block ; 
 int /*<<< orphan*/  endOnOutputSize ; 
 int /*<<< orphan*/  usingExtDict ; 

__attribute__((used)) static int LZ4_decompress_fast_extDict(const char *source, char *dest,
				       int originalSize,
				       const void *dictStart, size_t dictSize)
{
	return LZ4_decompress_generic(source, dest,
				      0, originalSize,
				      endOnOutputSize, decode_full_block,
				      usingExtDict, (BYTE *)dest,
				      (const BYTE *)dictStart, dictSize);
}