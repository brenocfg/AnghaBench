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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int MoveFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 

int wceex_rename(const char *oldfile, const char *newfile)
{
    int res;    
    size_t lenold;
    size_t lennew;
    wchar_t *wsold;
    wchar_t *wsnew;
    
    /* Covert filename buffer to Unicode. */

    /* Old filename */
    lenold = MultiByteToWideChar (CP_ACP, 0, oldfile, -1, NULL, 0) ;
    wsold = (wchar_t*)malloc(sizeof(wchar_t) * lenold);
    MultiByteToWideChar( CP_ACP, 0, oldfile, -1, wsold, lenold);
    
    /* New filename */
    lennew = MultiByteToWideChar (CP_ACP, 0, newfile, -1, NULL, 0) ;
    wsnew = (wchar_t*)malloc(sizeof(wchar_t) * lennew);
    MultiByteToWideChar(CP_ACP, 0, newfile, -1, wsnew, lennew);

    /* Delete file using Win32 CE API call */
    res = MoveFile(wsold, wsnew);
    
    /* Free wide-char string */
    free(wsold);
    free(wsnew);
    
    if (res)
        return 0; /* success */
    else
        return -1;
}