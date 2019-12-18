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

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int /*<<< orphan*/  NBLOOPS ; 
 int /*<<< orphan*/  NB_COMPRESSION_ALGORITHMS ; 
 int /*<<< orphan*/  NB_DECOMPRESSION_ALGORITHMS ; 

__attribute__((used)) static int usage_advanced(void)
{
    DISPLAY( "\nAdvanced options :\n");
    DISPLAY( " -c#    : test only compression function # [1-%i]\n", NB_COMPRESSION_ALGORITHMS);
    DISPLAY( " -d#    : test only decompression function # [1-%i]\n", NB_DECOMPRESSION_ALGORITHMS);
    DISPLAY( " -i#    : iteration loops [1-9](default : %i)\n", NBLOOPS);
    DISPLAY( " -B#    : Block size [4-7](default : 7)\n");
    return 0;
}