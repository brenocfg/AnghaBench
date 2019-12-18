#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  children; } ;
struct TYPE_11__ {TYPE_5__ hdr; } ;
typedef  TYPE_2__ ftp_session_t ;
typedef  int /*<<< orphan*/  WININETFTPFINDNEXTW ;
struct TYPE_10__ {int /*<<< orphan*/ * hInternet; int /*<<< orphan*/  entry; int /*<<< orphan*/  dwContext; int /*<<< orphan*/  htype; } ;
struct TYPE_12__ {int index; TYPE_1__ hdr; TYPE_2__* lpFtpSession; int /*<<< orphan*/ * lpafp; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__* LPWININETFTPFINDNEXTW ;
typedef  int /*<<< orphan*/  LPWIN32_FIND_DATAW ;
typedef  int /*<<< orphan*/ * LPFILEPROPERTIESW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FTPFINDNEXTVtbl ; 
 int /*<<< orphan*/  FTP_ConvertFileProp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FTP_ParseDirectory (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  WH_HFTPFINDNEXT ; 
 int /*<<< orphan*/  WININET_AddRef (TYPE_5__*) ; 
 TYPE_3__* alloc_object (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HINTERNET FTP_ReceiveFileList(ftp_session_t *lpwfs, INT nSocket, LPCWSTR lpszSearchFile,
	LPWIN32_FIND_DATAW lpFindFileData, DWORD_PTR dwContext)
{
    DWORD dwSize = 0;
    LPFILEPROPERTIESW lpafp = NULL;
    LPWININETFTPFINDNEXTW lpwfn = NULL;

    TRACE("(%p,%d,%s,%p,%08lx)\n", lpwfs, nSocket, debugstr_w(lpszSearchFile), lpFindFileData, dwContext);

    if (FTP_ParseDirectory(lpwfs, nSocket, lpszSearchFile, &lpafp, &dwSize))
    {
        if(lpFindFileData)
            FTP_ConvertFileProp(lpafp, lpFindFileData);

        lpwfn = alloc_object(&lpwfs->hdr, &FTPFINDNEXTVtbl, sizeof(WININETFTPFINDNEXTW));
        if (lpwfn)
        {
            lpwfn->hdr.htype = WH_HFTPFINDNEXT;
            lpwfn->hdr.dwContext = dwContext;
            lpwfn->index = 1; /* Next index is 1 since we return index 0 */
            lpwfn->size = dwSize;
            lpwfn->lpafp = lpafp;

            WININET_AddRef( &lpwfs->hdr );
            lpwfn->lpFtpSession = lpwfs;
            list_add_head( &lpwfs->hdr.children, &lpwfn->hdr.entry );
        }
    }

    TRACE("Matched %d files\n", dwSize);
    return lpwfn ? lpwfn->hdr.hInternet : NULL;
}