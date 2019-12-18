#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stat_t ;
struct TYPE_4__ {int /*<<< orphan*/ * dstFile; } ;
typedef  TYPE_1__ dRess_t ;
typedef  int /*<<< orphan*/  LZ4IO_prefs_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4IO_decompressSrcFile (int /*<<< orphan*/ * const,TYPE_1__,char const*,char const*) ; 
 int /*<<< orphan*/ * LZ4IO_openDstFile (int /*<<< orphan*/ * const,char const*) ; 
 scalar_t__ UTIL_getFileStat (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UTIL_setFileStat (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  nulmark ; 
 int /*<<< orphan*/  stdinmark ; 
 int /*<<< orphan*/  stdoutmark ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int LZ4IO_decompressDstFile(LZ4IO_prefs_t* const prefs, dRess_t ress, const char* input_filename, const char* output_filename)
{
    stat_t statbuf;
    int stat_result = 0;
    FILE* const foutput = LZ4IO_openDstFile(prefs, output_filename);
    if (foutput==NULL) return 1;   /* failure */

    if ( strcmp(input_filename, stdinmark)
      && UTIL_getFileStat(input_filename, &statbuf))
        stat_result = 1;

    ress.dstFile = foutput;
    LZ4IO_decompressSrcFile(prefs, ress, input_filename, output_filename);

    fclose(foutput);

    /* Copy owner, file permissions and modification time */
    if ( stat_result != 0
      && strcmp (output_filename, stdoutmark)
      && strcmp (output_filename, nulmark)) {
        UTIL_setFileStat(output_filename, &statbuf);
        /* should return value be read ? or is silent fail good enough ? */
    }

    return 0;
}