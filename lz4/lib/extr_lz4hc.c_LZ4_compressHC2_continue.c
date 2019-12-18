#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  internal_donotuse; } ;
typedef  TYPE_1__ LZ4_streamHC_t ;

/* Variables and functions */
 int LZ4HC_compress_generic (int /*<<< orphan*/ *,char const*,char*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notLimited ; 

int LZ4_compressHC2_continue (void* LZ4HC_Data, const char* src, char* dst, int srcSize, int cLevel)
{
    return LZ4HC_compress_generic (&((LZ4_streamHC_t*)LZ4HC_Data)->internal_donotuse, src, dst, &srcSize, 0, cLevel, notLimited);
}