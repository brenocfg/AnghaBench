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
 int /*<<< orphan*/  LZ4HC_CLEVEL_MAX ; 
 int /*<<< orphan*/  LZ4_EXTENSION ; 
 int /*<<< orphan*/  NULL_OUTPUT ; 
 scalar_t__ g_lz4c_legacy_commands ; 
 int /*<<< orphan*/  stdoutmark ; 
 int /*<<< orphan*/  usage_advanced (char const*) ; 

__attribute__((used)) static int usage_longhelp(const char* exeName)
{
    usage_advanced(exeName);
    DISPLAY( "\n");
    DISPLAY( "****************************\n");
    DISPLAY( "***** Advanced comment *****\n");
    DISPLAY( "****************************\n");
    DISPLAY( "\n");
    DISPLAY( "Which values can [output] have ? \n");
    DISPLAY( "---------------------------------\n");
    DISPLAY( "[output] : a filename \n");
    DISPLAY( "          '%s', or '-' for standard output (pipe mode)\n", stdoutmark);
    DISPLAY( "          '%s' to discard output (test mode) \n", NULL_OUTPUT);
    DISPLAY( "[output] can be left empty. In this case, it receives the following value :\n");
    DISPLAY( "          - if stdout is not the console, then [output] = stdout \n");
    DISPLAY( "          - if stdout is console : \n");
    DISPLAY( "               + for compression, output to filename%s \n", LZ4_EXTENSION);
    DISPLAY( "               + for decompression, output to filename without '%s'\n", LZ4_EXTENSION);
    DISPLAY( "                    > if input filename has no '%s' extension : error \n", LZ4_EXTENSION);
    DISPLAY( "\n");
    DISPLAY( "Compression levels : \n");
    DISPLAY( "---------------------\n");
    DISPLAY( "-0 ... -2  => Fast compression, all identicals\n");
    DISPLAY( "-3 ... -%d => High compression; higher number == more compression but slower\n", LZ4HC_CLEVEL_MAX);
    DISPLAY( "\n");
    DISPLAY( "stdin, stdout and the console : \n");
    DISPLAY( "--------------------------------\n");
    DISPLAY( "To protect the console from binary flooding (bad argument mistake)\n");
    DISPLAY( "%s will refuse to read from console, or write to console \n", exeName);
    DISPLAY( "except if '-c' command is specified, to force output to console \n");
    DISPLAY( "\n");
    DISPLAY( "Simple example :\n");
    DISPLAY( "----------------\n");
    DISPLAY( "1 : compress 'filename' fast, using default output name 'filename.lz4'\n");
    DISPLAY( "          %s filename\n", exeName);
    DISPLAY( "\n");
    DISPLAY( "Short arguments can be aggregated. For example :\n");
    DISPLAY( "----------------------------------\n");
    DISPLAY( "2 : compress 'filename' in high compression mode, overwrite output if exists\n");
    DISPLAY( "          %s -9 -f filename \n", exeName);
    DISPLAY( "    is equivalent to :\n");
    DISPLAY( "          %s -9f filename \n", exeName);
    DISPLAY( "\n");
    DISPLAY( "%s can be used in 'pure pipe mode'. For example :\n", exeName);
    DISPLAY( "-------------------------------------\n");
    DISPLAY( "3 : compress data stream from 'generator', send result to 'consumer'\n");
    DISPLAY( "          generator | %s | consumer \n", exeName);
    if (g_lz4c_legacy_commands) {
        DISPLAY( "\n");
        DISPLAY( "***** Warning  ***** \n");
        DISPLAY( "Legacy arguments take precedence. Therefore : \n");
        DISPLAY( "--------------------------------- \n");
        DISPLAY( "          %s -hc filename \n", exeName);
        DISPLAY( "means 'compress filename in high compression mode' \n");
        DISPLAY( "It is not equivalent to : \n");
        DISPLAY( "          %s -h -c filename \n", exeName);
        DISPLAY( "which displays help text and exits \n");
    }
    return 0;
}