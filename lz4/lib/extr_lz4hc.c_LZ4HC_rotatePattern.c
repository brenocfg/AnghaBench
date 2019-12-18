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
typedef  int /*<<< orphan*/  pattern ;
typedef  int /*<<< orphan*/  const U32 ;

/* Variables and functions */
 int /*<<< orphan*/  const LZ4HC_rotl32 (int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static U32 LZ4HC_rotatePattern(size_t const rotate, U32 const pattern)
{
    size_t const bitsToRotate = (rotate & (sizeof(pattern) - 1)) << 3;
    if (bitsToRotate == 0)
        return pattern;
    return LZ4HC_rotl32(pattern, (int)bitsToRotate);
}