#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sparseFileSupport; int /*<<< orphan*/  overwrite; } ;
typedef  TYPE_1__ LZ4IO_prefs_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int EOF ; 
 int /*<<< orphan*/  SET_BINARY_MODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_SPARSE_FILE_MODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int g_displayLevel ; 
 int getchar () ; 
 int /*<<< orphan*/  nulmark ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  stdoutmark ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static FILE* LZ4IO_openDstFile(LZ4IO_prefs_t* const prefs, const char* dstFileName)
{
    FILE* f;
    assert(dstFileName != NULL);

    if (!strcmp (dstFileName, stdoutmark)) {
        DISPLAYLEVEL(4,"Using stdout for output\n");
        f = stdout;
        SET_BINARY_MODE(stdout);
        if (prefs->sparseFileSupport==1) {
            prefs->sparseFileSupport = 0;
            DISPLAYLEVEL(4, "Sparse File Support is automatically disabled on stdout ; try --sparse \n");
        }
    } else {
        if (!prefs->overwrite && strcmp (dstFileName, nulmark)) {  /* Check if destination file already exists */
            f = fopen( dstFileName, "rb" );
            if (f != NULL) {  /* dest exists, prompt for overwrite authorization */
                fclose(f);
                if (g_displayLevel <= 1) {  /* No interaction possible */
                    DISPLAY("%s already exists; not overwritten  \n", dstFileName);
                    return NULL;
                }
                DISPLAY("%s already exists; do you wish to overwrite (y/N) ? ", dstFileName);
                {   int ch = getchar();
                    if ((ch!='Y') && (ch!='y')) {
                        DISPLAY("    not overwritten  \n");
                        return NULL;
                    }
                    while ((ch!=EOF) && (ch!='\n')) ch = getchar();  /* flush rest of input line */
        }   }   }
        f = fopen( dstFileName, "wb" );
        if (f==NULL) DISPLAYLEVEL(1, "%s: %s\n", dstFileName, strerror(errno));
    }

    /* sparse file */
    if (f && prefs->sparseFileSupport) { SET_SPARSE_FILE_MODE(f); }

    return f;
}