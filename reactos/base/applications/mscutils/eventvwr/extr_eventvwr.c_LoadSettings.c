#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  Value ;
struct TYPE_7__ {scalar_t__ MaximumLength; scalar_t__ Length; void* Buffer; } ;
typedef  TYPE_2__ UNICODE_STRING ;
struct TYPE_6__ {void* bottom; void* right; void* top; void* left; } ;
struct TYPE_8__ {int length; int showCmd; TYPE_1__ rcNormalPosition; } ;
struct TYPE_9__ {int bShowDetailsPane; int bShowGrid; int bSaveSettings; int bNewestEventsFirst; int nVSplitPos; int nHSplitPos; TYPE_3__ wpPos; } ;
typedef  void* PWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  void* BOOL ;

/* Variables and functions */
 void* CW_USEDEFAULT ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  EVNTVWR_PARAM_KEY ; 
 void* FALSE ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 scalar_t__ REG_DWORD ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  RtlUnicodeStringToInteger (TYPE_2__*,int,scalar_t__*) ; 
 TYPE_4__ Settings ; 
 void* TRUE ; 
 int /*<<< orphan*/  UNICODE_NULL ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 
 int swscanf (int /*<<< orphan*/ *,char*,void**,void**,void**,void**,int*) ; 

BOOL
LoadSettings(int nDefCmdShow)
{
    HKEY hKeyEventVwr;
    LONG Result;
    DWORD dwSize;
    DWORD dwType;
    DWORD Value;
    UNICODE_STRING ValueU;
    WCHAR buffer[100];

    /* Load the default values */
    Settings.bShowDetailsPane = TRUE;
    Settings.bShowGrid = FALSE;
    Settings.bSaveSettings = TRUE;
    Settings.bNewestEventsFirst = TRUE;
    Settings.nVSplitPos = 250; /* Splitter default positions */
    Settings.nHSplitPos = 250;
    ZeroMemory(&Settings.wpPos, sizeof(Settings.wpPos));
    Settings.wpPos.length = sizeof(Settings.wpPos);
    Settings.wpPos.rcNormalPosition.left = CW_USEDEFAULT;
    Settings.wpPos.rcNormalPosition.top  = CW_USEDEFAULT;
    Settings.wpPos.rcNormalPosition.right  = CW_USEDEFAULT;
    Settings.wpPos.rcNormalPosition.bottom = CW_USEDEFAULT;

    /* Try to create/open the Event Viewer user key */
    if (RegCreateKeyExW(HKEY_CURRENT_USER,
                        EVNTVWR_PARAM_KEY,
                        0,
                        NULL,
                        REG_OPTION_NON_VOLATILE,
                        KEY_READ | KEY_WRITE,
                        NULL,
                        &hKeyEventVwr,
                        NULL) != ERROR_SUCCESS)
    {
        return FALSE;
    }

    // Result = RegQueryValueExW(hKeyEventVwr, L"Filter", NULL, &dwType, (LPBYTE)&szFilter, &dwSize); // REG_SZ
    // Result = RegQueryValueExW(hKeyEventVwr, L"Find", NULL, &dwType, (LPBYTE)&szFind, &dwSize); // REG_SZ
    // Result = RegQueryValueExW(hKeyEventVwr, L"Module", NULL, &dwType, (LPBYTE)&szModule, &dwSize); // REG_SZ

    dwSize = sizeof(Value);
    Result = RegQueryValueExW(hKeyEventVwr, L"DetailsPane", NULL, &dwType, (LPBYTE)&Value, &dwSize);
    if ((Result == ERROR_SUCCESS) && (dwType == REG_SZ || dwType == REG_DWORD))
    {
        if (dwType == REG_SZ)
        {
            ValueU.Buffer = (PWSTR)&Value;
            ValueU.Length = ValueU.MaximumLength = dwSize;
            RtlUnicodeStringToInteger(&ValueU, 10, &Value);
        }
        Settings.bShowDetailsPane = !!Value;
    }

    dwSize = sizeof(Value);
    Result = RegQueryValueExW(hKeyEventVwr, L"ShowGrid", NULL, &dwType, (LPBYTE)&Value, &dwSize);
    if ((Result == ERROR_SUCCESS) && (dwType == REG_SZ || dwType == REG_DWORD))
    {
        if (dwType == REG_SZ)
        {
            ValueU.Buffer = (PWSTR)&Value;
            ValueU.Length = ValueU.MaximumLength = dwSize;
            RtlUnicodeStringToInteger(&ValueU, 10, &Value);
        }
        Settings.bShowGrid = !!Value;
    }

    dwSize = sizeof(Value);
    Result = RegQueryValueExW(hKeyEventVwr, L"SortOrder", NULL, &dwType, (LPBYTE)&Value, &dwSize);
    if ((Result == ERROR_SUCCESS) && (dwType == REG_SZ || dwType == REG_DWORD))
    {
        if (dwType == REG_SZ)
        {
            ValueU.Buffer = (PWSTR)&Value;
            ValueU.Length = ValueU.MaximumLength = dwSize;
            RtlUnicodeStringToInteger(&ValueU, 10, &Value);
        }
        Settings.bNewestEventsFirst = !!Value;
    }

    /* Retrieve the splitter positions */
    dwSize = sizeof(Value);
    Result = RegQueryValueExW(hKeyEventVwr, L"VSplitPos", NULL, &dwType, (LPBYTE)&Value, &dwSize);
    if ((Result == ERROR_SUCCESS) && (dwType == REG_SZ || dwType == REG_DWORD))
    {
        if (dwType == REG_SZ)
        {
            ValueU.Buffer = (PWSTR)&Value;
            ValueU.Length = ValueU.MaximumLength = dwSize;
            RtlUnicodeStringToInteger(&ValueU, 10, &Value);
        }
        Settings.nVSplitPos = Value;
    }

    dwSize = sizeof(Value);
    Result = RegQueryValueExW(hKeyEventVwr, L"HSplitPos", NULL, &dwType, (LPBYTE)&Value, &dwSize);
    if ((Result == ERROR_SUCCESS) && (dwType == REG_SZ || dwType == REG_DWORD))
    {
        if (dwType == REG_SZ)
        {
            ValueU.Buffer = (PWSTR)&Value;
            ValueU.Length = ValueU.MaximumLength = dwSize;
            RtlUnicodeStringToInteger(&ValueU, 10, &Value);
        }
        Settings.nHSplitPos = Value;
    }

    /* Retrieve the geometry of the main window */
    dwSize = sizeof(buffer);
    Result = RegQueryValueExW(hKeyEventVwr, L"Window", NULL, &dwType, (LPBYTE)buffer, &dwSize);
    if ((Result != ERROR_SUCCESS) || (dwType != REG_SZ))
        buffer[0] = UNICODE_NULL;

    if (swscanf(buffer, L"%d %d %d %d %d",
                &Settings.wpPos.rcNormalPosition.left,
                &Settings.wpPos.rcNormalPosition.top,
                &Settings.wpPos.rcNormalPosition.right,
                &Settings.wpPos.rcNormalPosition.bottom,
                &Settings.wpPos.showCmd) != 5)
    {
        /* Parsing failed, use defaults */
        Settings.wpPos.rcNormalPosition.left = CW_USEDEFAULT;
        Settings.wpPos.rcNormalPosition.top  = CW_USEDEFAULT;
        Settings.wpPos.rcNormalPosition.right  = CW_USEDEFAULT;
        Settings.wpPos.rcNormalPosition.bottom = CW_USEDEFAULT;
        Settings.wpPos.showCmd = nDefCmdShow; // SW_SHOWNORMAL;
    }

    dwSize = sizeof(Value);
    Result = RegQueryValueExW(hKeyEventVwr, L"SaveSettings", NULL, &dwType, (LPBYTE)&Value, &dwSize);
    if ((Result == ERROR_SUCCESS) && (dwType == REG_SZ || dwType == REG_DWORD))
    {
        if (dwType == REG_SZ)
        {
            ValueU.Buffer = (PWSTR)&Value;
            ValueU.Length = ValueU.MaximumLength = dwSize;
            RtlUnicodeStringToInteger(&ValueU, 10, &Value);
        }
        Settings.bSaveSettings = !!Value;
    }

    RegCloseKey(hKeyEventVwr);
    return TRUE;
}