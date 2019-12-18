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
struct compressionParameters {int /*<<< orphan*/  cLevel; } ;

/* Variables and functions */
 int LZ4_compress_HC (char const*,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int LZ4_compressBlockNoStreamHC(
    const struct compressionParameters* pThis,
    const char* src, char* dst,
    int srcSize, int dstSize)
{
    return LZ4_compress_HC(src, dst, srcSize, dstSize, pThis->cLevel);
}