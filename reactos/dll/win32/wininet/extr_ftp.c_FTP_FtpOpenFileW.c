#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uc ;
struct TYPE_20__ {int /*<<< orphan*/  dwContext; int /*<<< orphan*/  children; } ;
struct TYPE_23__ {int lstnSocket; TYPE_10__ hdr; TYPE_5__* lpAppInfo; int /*<<< orphan*/  lpszUserName; int /*<<< orphan*/  serverport; int /*<<< orphan*/  servername; TYPE_4__* download_in_progress; } ;
typedef  TYPE_3__ ftp_session_t ;
struct TYPE_22__ {void* hInternet; int /*<<< orphan*/  entry; void* dwContext; scalar_t__ dwFlags; int /*<<< orphan*/  htype; } ;
struct TYPE_24__ {scalar_t__ cache_file_handle; TYPE_2__ hdr; int /*<<< orphan*/ * cache_file; TYPE_3__* lpFtpSession; void* session_deleted; int /*<<< orphan*/  nDataSocket; } ;
typedef  TYPE_4__ ftp_file_t ;
struct TYPE_21__ {int dwFlags; } ;
struct TYPE_25__ {TYPE_1__ hdr; } ;
typedef  TYPE_5__ appinfo_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_26__ {int dwStructSize; int /*<<< orphan*/ * lpszUrlPath; int /*<<< orphan*/  lpszUserName; int /*<<< orphan*/  nPort; int /*<<< orphan*/  lpszHostName; int /*<<< orphan*/  nScheme; } ;
typedef  TYPE_6__ URL_COMPONENTSW ;
struct TYPE_27__ {int /*<<< orphan*/  dwError; void* dwResult; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  TYPE_7__ INTERNET_ASYNC_RESULT ;
typedef  int /*<<< orphan*/  INT ;
typedef  void* HINTERNET ;
typedef  void* DWORD_PTR ;
typedef  scalar_t__ DWORD ;
typedef  void* BOOL ;

/* Variables and functions */
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateUrlCacheEntryW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 void* FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  FTPFILEVtbl ; 
 scalar_t__ FTP_GetDataSocket (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FTP_ReceiveRequestData (TYPE_4__*,int /*<<< orphan*/ ) ; 
 void* FTP_SendRetrieve (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__) ; 
 void* FTP_SendStore (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ GENERIC_READ ; 
 scalar_t__ GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 int INTERNET_FLAG_ASYNC ; 
 int /*<<< orphan*/  INTERNET_GetLastError () ; 
 int /*<<< orphan*/  INTERNET_SCHEME_FTP ; 
 int /*<<< orphan*/  INTERNET_STATUS_HANDLE_CREATED ; 
 int /*<<< orphan*/  INTERNET_STATUS_REQUEST_COMPLETE ; 
 int /*<<< orphan*/  INTERNET_SendCallback (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int) ; 
 int /*<<< orphan*/  INTERNET_SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ InternetCreateUrlW (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 int /*<<< orphan*/  WH_HFILE ; 
 int /*<<< orphan*/  WININET_AddRef (TYPE_10__*) ; 
 TYPE_4__* alloc_object (TYPE_10__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/ * heap_alloc (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 void* heap_strdupW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HINTERNET FTP_FtpOpenFileW(ftp_session_t *lpwfs,
	LPCWSTR lpszFileName, DWORD fdwAccess, DWORD dwFlags,
	DWORD_PTR dwContext)
{
    INT nDataSocket;
    BOOL bSuccess = FALSE;
    ftp_file_t *lpwh = NULL;
    appinfo_t *hIC = NULL;

    TRACE("\n");

    /* Clear any error information */
    INTERNET_SetLastError(0);

    if (GENERIC_READ == fdwAccess)
    {
        /* Set up socket to retrieve data */
        bSuccess = FTP_SendRetrieve(lpwfs, lpszFileName, dwFlags);
    }
    else if (GENERIC_WRITE == fdwAccess)
    {
        /* Set up socket to send data */
        bSuccess = FTP_SendStore(lpwfs, lpszFileName, dwFlags);
    }

    /* Get data socket to server */
    if (bSuccess && FTP_GetDataSocket(lpwfs, &nDataSocket))
    {
        lpwh = alloc_object(&lpwfs->hdr, &FTPFILEVtbl, sizeof(ftp_file_t));
        lpwh->hdr.htype = WH_HFILE;
        lpwh->hdr.dwFlags = dwFlags;
        lpwh->hdr.dwContext = dwContext;
        lpwh->nDataSocket = nDataSocket;
        lpwh->cache_file = NULL;
        lpwh->cache_file_handle = INVALID_HANDLE_VALUE;
        lpwh->session_deleted = FALSE;

        WININET_AddRef( &lpwfs->hdr );
        lpwh->lpFtpSession = lpwfs;
        list_add_head( &lpwfs->hdr.children, &lpwh->hdr.entry );
	
	/* Indicate that a download is currently in progress */
	lpwfs->download_in_progress = lpwh;
    }

    if (lpwfs->lstnSocket != -1)
    {
        closesocket(lpwfs->lstnSocket);
        lpwfs->lstnSocket = -1;
    }

    if (bSuccess && fdwAccess == GENERIC_READ)
    {
        WCHAR filename[MAX_PATH + 1];
        URL_COMPONENTSW uc;
        DWORD len;

        memset(&uc, 0, sizeof(uc));
        uc.dwStructSize = sizeof(uc);
        uc.nScheme      = INTERNET_SCHEME_FTP;
        uc.lpszHostName = lpwfs->servername;
        uc.nPort        = lpwfs->serverport;
        uc.lpszUserName = lpwfs->lpszUserName;
        uc.lpszUrlPath  = heap_strdupW(lpszFileName);

        if (!InternetCreateUrlW(&uc, 0, NULL, &len) && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            WCHAR *url = heap_alloc(len * sizeof(WCHAR));

            if (url && InternetCreateUrlW(&uc, 0, url, &len) && CreateUrlCacheEntryW(url, 0, NULL, filename, 0))
            {
                lpwh->cache_file = heap_strdupW(filename);
                lpwh->cache_file_handle = CreateFileW(filename, GENERIC_WRITE, FILE_SHARE_READ,
                                                      NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                if (lpwh->cache_file_handle == INVALID_HANDLE_VALUE)
                {
                    WARN("Could not create cache file: %u\n", GetLastError());
                    heap_free(lpwh->cache_file);
                    lpwh->cache_file = NULL;
                }
            }
            heap_free(url);
        }
        heap_free(uc.lpszUrlPath);
    }

    hIC = lpwfs->lpAppInfo;
    if (hIC->hdr.dwFlags & INTERNET_FLAG_ASYNC)
    {
        INTERNET_ASYNC_RESULT iar;

	if (lpwh)
	{
            iar.dwResult = (DWORD_PTR)lpwh->hdr.hInternet;
            iar.dwError = ERROR_SUCCESS;
            INTERNET_SendCallback(&lpwfs->hdr, lpwfs->hdr.dwContext, INTERNET_STATUS_HANDLE_CREATED,
                &iar, sizeof(INTERNET_ASYNC_RESULT));
	}

        if(bSuccess) {
            FTP_ReceiveRequestData(lpwh, TRUE);
        }else {
            iar.dwResult = 0;
            iar.dwError = INTERNET_GetLastError();
            INTERNET_SendCallback(&lpwfs->hdr, lpwfs->hdr.dwContext, INTERNET_STATUS_REQUEST_COMPLETE,
                    &iar, sizeof(INTERNET_ASYNC_RESULT));
        }
    }

    if(!bSuccess)
        return FALSE;

    return lpwh->hdr.hInternet;
}