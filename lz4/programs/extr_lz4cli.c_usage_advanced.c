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
 char* WELCOME_MESSAGE ; 
 scalar_t__ g_lz4c_legacy_commands ; 
 int /*<<< orphan*/  usage (char const*) ; 

__attribute__((used)) static int usage_advanced(const char* exeName)
{
    DISPLAY(WELCOME_MESSAGE);
    usage(exeName);
    DISPLAY( "\n");
    DISPLAY( "Advanced arguments :\n");
    DISPLAY( " -V     : display Version number and exit \n");
    DISPLAY( " -v     : verbose mode \n");
    DISPLAY( " -q     : suppress warnings; specify twice to suppress errors too\n");
    DISPLAY( " -c     : force write to standard output, even if it is the console\n");
    DISPLAY( " -t     : test compressed file integrity\n");
    DISPLAY( " -m     : multiple input files (implies automatic output filenames)\n");
#ifdef UTIL_HAS_CREATEFILELIST
    DISPLAY( " -r     : operate recursively on directories (sets also -m) \n");
#endif
    DISPLAY( " -l     : compress using Legacy format (Linux kernel compression)\n");
    DISPLAY( " -B#    : cut file into blocks of size # bytes [32+] \n");
    DISPLAY( "                     or predefined block size [4-7] (default: 7) \n");
    DISPLAY( " -BI    : Block Independence (default) \n");
    DISPLAY( " -BD    : Block dependency (improves compression ratio) \n");
    DISPLAY( " -BX    : enable block checksum (default:disabled) \n");
    DISPLAY( "--no-frame-crc : disable stream checksum (default:enabled) \n");
    DISPLAY( "--content-size : compressed frame includes original size (default:not present)\n");
    DISPLAY( "--list FILE : lists information about .lz4 files (useful for files compressed with --content-size flag)\n");
    DISPLAY( "--[no-]sparse  : sparse mode (default:enabled on file, disabled on stdout)\n");
    DISPLAY( "--favor-decSpeed: compressed files decompress faster, but are less compressed \n");
    DISPLAY( "--fast[=#]: switch to ultra fast compression level (default: %i)\n", 1);
    DISPLAY( "--best  : same as -%d\n", LZ4HC_CLEVEL_MAX);
    DISPLAY( "Benchmark arguments : \n");
    DISPLAY( " -b#    : benchmark file(s), using # compression level (default : 1) \n");
    DISPLAY( " -e#    : test all compression levels from -bX to # (default : 1)\n");
    DISPLAY( " -i#    : minimum evaluation time in seconds (default : 3s) \n");
    if (g_lz4c_legacy_commands) {
        DISPLAY( "Legacy arguments : \n");
        DISPLAY( " -c0    : fast compression \n");
        DISPLAY( " -c1    : high compression \n");
        DISPLAY( " -c2,-hc: very high compression \n");
        DISPLAY( " -y     : overwrite output without prompting \n");
    }
    return 0;
}