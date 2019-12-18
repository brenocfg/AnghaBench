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
typedef  scalar_t__ clock_t ;
typedef  int /*<<< orphan*/  cRess_t ;
typedef  int /*<<< orphan*/  UTIL_time_t ;
typedef  scalar_t__ U64 ;
typedef  int /*<<< orphan*/  LZ4IO_prefs_t ;

/* Variables and functions */
 double CLOCKS_PER_SEC ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,double const,double const) ; 
 int LZ4IO_compressFilename_extRess (int /*<<< orphan*/ * const,int /*<<< orphan*/  const,char const*,char const*,int) ; 
 int /*<<< orphan*/  LZ4IO_createCResources (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  LZ4IO_freeCResources (int /*<<< orphan*/  const) ; 
 scalar_t__ UTIL_clockSpanNano (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  UTIL_getTime () ; 
 scalar_t__ clock () ; 

int LZ4IO_compressFilename(LZ4IO_prefs_t* const prefs, const char* srcFileName, const char* dstFileName, int compressionLevel)
{
    UTIL_time_t const timeStart = UTIL_getTime();
    clock_t const cpuStart = clock();
    cRess_t const ress = LZ4IO_createCResources(prefs);

    int const result = LZ4IO_compressFilename_extRess(prefs, ress, srcFileName, dstFileName, compressionLevel);

    /* Free resources */
    LZ4IO_freeCResources(ress);

    /* Final Status */
    {   clock_t const cpuEnd = clock();
        double const cpuLoad_s = (double)(cpuEnd - cpuStart) / CLOCKS_PER_SEC;
        U64 const timeLength_ns = UTIL_clockSpanNano(timeStart);
        double const timeLength_s = (double)timeLength_ns / 1000000000;
        DISPLAYLEVEL(4, "Completed in %.2f sec  (cpu load : %.0f%%)\n",
                        timeLength_s, (cpuLoad_s / timeLength_s) * 100);
    }

    return result;
}