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
typedef  int /*<<< orphan*/  dRess_t ;
typedef  scalar_t__ clock_t ;
typedef  int /*<<< orphan*/  LZ4IO_prefs_t ;

/* Variables and functions */
 double CLOCKS_PER_SEC ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,double const) ; 
 int /*<<< orphan*/  LZ4IO_createDResources (int /*<<< orphan*/ * const) ; 
 int LZ4IO_decompressDstFile (int /*<<< orphan*/ * const,int /*<<< orphan*/  const,char const*,char const*) ; 
 int /*<<< orphan*/  LZ4IO_freeDResources (int /*<<< orphan*/  const) ; 
 scalar_t__ clock () ; 

int LZ4IO_decompressFilename(LZ4IO_prefs_t* const prefs, const char* input_filename, const char* output_filename)
{
    dRess_t const ress = LZ4IO_createDResources(prefs);
    clock_t const start = clock();

    int const missingFiles = LZ4IO_decompressDstFile(prefs, ress, input_filename, output_filename);

    clock_t const end = clock();
    double const seconds = (double)(end - start) / CLOCKS_PER_SEC;
    DISPLAYLEVEL(4, "Done in %.2f sec  \n", seconds);

    LZ4IO_freeDResources(ress);
    return missingFiles;
}