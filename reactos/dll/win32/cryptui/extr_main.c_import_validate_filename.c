#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ hCertStore; } ;
struct TYPE_4__ {TYPE_1__ u; int /*<<< orphan*/  dwSubjectChoice; } ;
struct ImportWizData {int /*<<< orphan*/ * pwszWizardTitle; int /*<<< orphan*/  dwFlags; void* freeSource; TYPE_2__ importSrc; int /*<<< orphan*/  contentType; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HCERTSTORE ;
typedef  scalar_t__ HANDLE ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTUI_WIZ_IMPORT_SUBJECT_CERT_STORE ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int /*<<< orphan*/  FormatMessageW (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IDS_IMPORT_BAD_FORMAT ; 
 int /*<<< orphan*/  IDS_IMPORT_OPEN_FAILED ; 
 int IDS_IMPORT_TYPE_MISMATCH ; 
 int /*<<< orphan*/  IDS_IMPORT_WIZARD ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int MAX_STRING_LEN ; 
 int MB_ICONERROR ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 void* TRUE ; 
 int /*<<< orphan*/  check_store_context_type (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hInstance ; 
 int /*<<< orphan*/  import_warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 scalar_t__ open_store_from_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL import_validate_filename(HWND hwnd, struct ImportWizData *data,
 LPCWSTR fileName)
{
    HANDLE file;
    BOOL ret = FALSE;

    file = CreateFileW(fileName, GENERIC_READ, FILE_SHARE_READ, NULL,
     OPEN_EXISTING, 0, NULL);
    if (file != INVALID_HANDLE_VALUE)
    {
        HCERTSTORE source = open_store_from_file(data->dwFlags, fileName,
         &data->contentType);
        int warningID = 0;

        if (!source)
            warningID = IDS_IMPORT_BAD_FORMAT;
        else if (!check_store_context_type(data->dwFlags, source))
            warningID = IDS_IMPORT_TYPE_MISMATCH;
        else
        {
            data->importSrc.dwSubjectChoice =
             CRYPTUI_WIZ_IMPORT_SUBJECT_CERT_STORE;
            data->importSrc.u.hCertStore = source;
            data->freeSource = TRUE;
            ret = TRUE;
        }
        if (warningID)
        {
            import_warning(data->dwFlags, hwnd, data->pwszWizardTitle,
             warningID);
        }
        CloseHandle(file);
    }
    else
    {
        WCHAR title[MAX_STRING_LEN], error[MAX_STRING_LEN];
        LPCWSTR pTitle;
        LPWSTR msgBuf, fullError;

        if (data->pwszWizardTitle)
            pTitle = data->pwszWizardTitle;
        else
        {
            LoadStringW(hInstance, IDS_IMPORT_WIZARD, title, ARRAY_SIZE(title));
            pTitle = title;
        }
        LoadStringW(hInstance, IDS_IMPORT_OPEN_FAILED, error, ARRAY_SIZE(error));
        FormatMessageW(
         FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
         GetLastError(), 0, (LPWSTR) &msgBuf, 0, NULL);
        fullError = HeapAlloc(GetProcessHeap(), 0,
         (lstrlenW(error) + lstrlenW(fileName) + lstrlenW(msgBuf) + 3)
         * sizeof(WCHAR));
        if (fullError)
        {
            LPWSTR ptr = fullError;

            lstrcpyW(ptr, error);
            ptr += lstrlenW(error);
            lstrcpyW(ptr, fileName);
            ptr += lstrlenW(fileName);
            *ptr++ = ':';
            *ptr++ = '\n';
            lstrcpyW(ptr, msgBuf);
            MessageBoxW(hwnd, fullError, pTitle, MB_ICONERROR | MB_OK);
            HeapFree(GetProcessHeap(), 0, fullError);
        }
        LocalFree(msgBuf);
    }
    return ret;
}