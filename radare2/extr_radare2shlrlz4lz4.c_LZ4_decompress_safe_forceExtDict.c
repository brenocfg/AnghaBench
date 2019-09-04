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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
 int LZ4_decompress_generic (char const*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  endOnInputSize ; 
 int /*<<< orphan*/  full ; 
 int /*<<< orphan*/  usingExtDict ; 

int LZ4_decompress_safe_forceExtDict(const char* source, char* dest, int compressedSize, int maxOutputSize, const char* dictStart, int dictSize) {
	return LZ4_decompress_generic(source, dest, compressedSize, maxOutputSize, endOnInputSize, full, 0, usingExtDict, (ut8*)dest, (const ut8*)dictStart, dictSize);
}