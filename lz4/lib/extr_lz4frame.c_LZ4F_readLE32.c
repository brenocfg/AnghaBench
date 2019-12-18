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
typedef  int U32 ;
typedef  int BYTE ;

/* Variables and functions */

__attribute__((used)) static U32 LZ4F_readLE32 (const void* src)
{
    const BYTE* const srcPtr = (const BYTE*)src;
    U32 value32 = srcPtr[0];
    value32 += ((U32)srcPtr[1])<< 8;
    value32 += ((U32)srcPtr[2])<<16;
    value32 += ((U32)srcPtr[3])<<24;
    return value32;
}