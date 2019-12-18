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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 

void wceex_rewind(FILE * fp)
{
    int ret;

    /* TODO - mloskot: WARNING!
     * fseek() does not clear error and end-of-file indicators for the stream
     * So, that's why dirty asserts are used to get informed about potential problems.
     */
    ret = fseek(fp, 0L, SEEK_SET);
    
    assert(0 == ret);
    assert(0 == ferror(fp));
    assert(!feof(fp));

    /*

    // XXX - mloskot:
    // FILE* to HANDLE conversion needs hacks like _get_osfhandle()
    // which are not available on Windows CE.
    // Simple cast does not work.
    //
    // TODO: Does anyone know how to convert FILE* to HANDLE?

    DWORD dwError;
    HANDLE hFile;

    hFile = (void*)fp;

    if (0xFFFFFFFF == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
    {
    	dwError = GetLastError();
        assert(NO_ERROR == dwError);
    }

    */
}