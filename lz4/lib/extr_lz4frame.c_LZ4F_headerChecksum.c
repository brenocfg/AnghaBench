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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int XXH32 (void const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BYTE LZ4F_headerChecksum (const void* header, size_t length)
{
    U32 const xxh = XXH32(header, length, 0);
    return (BYTE)(xxh >> 8);
}