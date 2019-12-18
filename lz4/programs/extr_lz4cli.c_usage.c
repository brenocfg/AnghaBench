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
 int /*<<< orphan*/  LZ4_EXTENSION ; 
 int /*<<< orphan*/  stdinmark ; 

__attribute__((used)) static int usage(const char* exeName)
{
    DISPLAY( "Usage : \n");
    DISPLAY( "      %s [arg] [input] [output] \n", exeName);
    DISPLAY( "\n");
    DISPLAY( "input   : a filename \n");
    DISPLAY( "          with no FILE, or when FILE is - or %s, read standard input\n", stdinmark);
    DISPLAY( "Arguments : \n");
    DISPLAY( " -1     : Fast compression (default) \n");
    DISPLAY( " -9     : High compression \n");
    DISPLAY( " -d     : decompression (default for %s extension)\n", LZ4_EXTENSION);
    DISPLAY( " -z     : force compression \n");
    DISPLAY( " -D FILE: use FILE as dictionary \n");
    DISPLAY( " -f     : overwrite output without prompting \n");
    DISPLAY( " -k     : preserve source files(s)  (default) \n");
    DISPLAY( "--rm    : remove source file(s) after successful de/compression \n");
    DISPLAY( " -h/-H  : display help/long help and exit \n");
    return 0;
}