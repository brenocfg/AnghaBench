#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * dstFile; } ;
typedef  TYPE_1__ dRess_t ;
struct TYPE_8__ {scalar_t__ removeSrcFile; } ;
typedef  TYPE_2__ LZ4IO_prefs_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const*,...) ; 
 unsigned long long const ENDOFSTREAM ; 
 int /*<<< orphan*/  EXM_THROW (int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LZ4IO_openSrcFile (char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 scalar_t__ remove (char const*) ; 
 unsigned long long selectDecoder (TYPE_2__* const,TYPE_1__,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int LZ4IO_decompressSrcFile(LZ4IO_prefs_t* const prefs, dRess_t ress, const char* input_filename, const char* output_filename)
{
    FILE* const foutput = ress.dstFile;
    unsigned long long filesize = 0;

    /* Init */
    FILE* const finput = LZ4IO_openSrcFile(input_filename);
    if (finput==NULL) return 1;

    /* Loop over multiple streams */
    for ( ; ; ) {  /* endless loop, see break condition */
        unsigned long long const decodedSize =
                        selectDecoder(prefs, ress, finput, foutput);
        if (decodedSize == ENDOFSTREAM) break;
        filesize += decodedSize;
    }

    /* Close input */
    fclose(finput);
    if (prefs->removeSrcFile) {  /* --rm */
        if (remove(input_filename))
            EXM_THROW(45, "Remove error : %s: %s", input_filename, strerror(errno));
    }

    /* Final Status */
    DISPLAYLEVEL(2, "\r%79s\r", "");
    DISPLAYLEVEL(2, "%-20.20s : decoded %llu bytes \n", input_filename, filesize);
    (void)output_filename;

    return 0;
}