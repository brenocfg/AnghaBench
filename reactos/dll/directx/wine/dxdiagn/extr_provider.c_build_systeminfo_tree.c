#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msex ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  __ms_va_list ;
typedef  char WCHAR ;
struct TYPE_7__ {int dwLength; int ullTotalPhys; int ullTotalPageFile; int ullAvailPageFile; } ;
struct TYPE_6__ {int dwOSVersionInfoSize; int dwMajorVersion; int dwMinorVersion; int dwBuildNumber; int dwPlatformId; char const* szCSDVersion; } ;
typedef  TYPE_1__ OSVERSIONINFOW ;
typedef  TYPE_2__ MEMORYSTATUSEX ;
typedef  int /*<<< orphan*/  IDxDiagContainerImpl_Container ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  char* DWORD_PTR ;
typedef  char* DWORD ;

/* Variables and functions */
 char* ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int FORMAT_MESSAGE_ARGUMENT_ARRAY ; 
 int FORMAT_MESSAGE_FROM_STRING ; 
 int /*<<< orphan*/  FormatMessageW (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetComputerNameW (char*,char**) ; 
 int /*<<< orphan*/  GetVersionExW (TYPE_1__*) ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (char*,int) ; 
 int /*<<< orphan*/  GlobalMemoryStatusEx (TYPE_2__*) ; 
 int /*<<< orphan*/  IDS_PAGE_FILE_FORMAT ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  MAX_COMPUTERNAME_LENGTH ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  add_bool_property (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_bstr_property (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  add_ui4_property (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  add_ull_as_bstr_property (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  dxdiagn_instance ; 
 int /*<<< orphan*/  fill_datetime_information (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_language_information (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_os_string_information (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fill_processor_information (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_netmeeting_running () ; 
 int /*<<< orphan*/  swprintf (char*,char const*,char*,...) ; 
 char const* szEmpty ; 

__attribute__((used)) static HRESULT build_systeminfo_tree(IDxDiagContainerImpl_Container *node)
{
    static const WCHAR dwDirectXVersionMajor[] = {'d','w','D','i','r','e','c','t','X','V','e','r','s','i','o','n','M','a','j','o','r',0};
    static const WCHAR dwDirectXVersionMinor[] = {'d','w','D','i','r','e','c','t','X','V','e','r','s','i','o','n','M','i','n','o','r',0};
    static const WCHAR szDirectXVersionLetter[] = {'s','z','D','i','r','e','c','t','X','V','e','r','s','i','o','n','L','e','t','t','e','r',0};
    static const WCHAR szDirectXVersionLetter_v[] = {'c',0};
    static const WCHAR bDebug[] = {'b','D','e','b','u','g',0};
    static const WCHAR bNECPC98[] = {'b','N','E','C','P','C','9','8',0};
    static const WCHAR szDirectXVersionEnglish[] = {'s','z','D','i','r','e','c','t','X','V','e','r','s','i','o','n','E','n','g','l','i','s','h',0};
    static const WCHAR szDirectXVersionEnglish_v[] = {'4','.','0','9','.','0','0','0','0','.','0','9','0','4',0};
    static const WCHAR szDirectXVersionLongEnglish[] = {'s','z','D','i','r','e','c','t','X','V','e','r','s','i','o','n','L','o','n','g','E','n','g','l','i','s','h',0};
    static const WCHAR szDirectXVersionLongEnglish_v[] = {'=',' ','"','D','i','r','e','c','t','X',' ','9','.','0','c',' ','(','4','.','0','9','.','0','0','0','0','.','0','9','0','4',')',0};
    static const WCHAR ullPhysicalMemory[] = {'u','l','l','P','h','y','s','i','c','a','l','M','e','m','o','r','y',0};
    static const WCHAR ullUsedPageFile[]   = {'u','l','l','U','s','e','d','P','a','g','e','F','i','l','e',0};
    static const WCHAR ullAvailPageFile[]  = {'u','l','l','A','v','a','i','l','P','a','g','e','F','i','l','e',0};
    static const WCHAR bNetMeetingRunning[] = {'b','N','e','t','M','e','e','t','i','n','g','R','u','n','n','i','n','g',0};
    static const WCHAR szWindowsDir[] = {'s','z','W','i','n','d','o','w','s','D','i','r',0};
    static const WCHAR dwOSMajorVersion[] = {'d','w','O','S','M','a','j','o','r','V','e','r','s','i','o','n',0};
    static const WCHAR dwOSMinorVersion[] = {'d','w','O','S','M','i','n','o','r','V','e','r','s','i','o','n',0};
    static const WCHAR dwOSBuildNumber[] = {'d','w','O','S','B','u','i','l','d','N','u','m','b','e','r',0};
    static const WCHAR dwOSPlatformID[] = {'d','w','O','S','P','l','a','t','f','o','r','m','I','D',0};
    static const WCHAR szCSDVersion[] = {'s','z','C','S','D','V','e','r','s','i','o','n',0};
    static const WCHAR szPhysicalMemoryEnglish[] = {'s','z','P','h','y','s','i','c','a','l','M','e','m','o','r','y','E','n','g','l','i','s','h',0};
    static const WCHAR szPageFileLocalized[] = {'s','z','P','a','g','e','F','i','l','e','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szPageFileEnglish[] = {'s','z','P','a','g','e','F','i','l','e','E','n','g','l','i','s','h',0};
    static const WCHAR szMachineNameLocalized[] = {'s','z','M','a','c','h','i','n','e','N','a','m','e','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szMachineNameEnglish[] = {'s','z','M','a','c','h','i','n','e','N','a','m','e','E','n','g','l','i','s','h',0};
    static const WCHAR szSystemManufacturerEnglish[] = {'s','z','S','y','s','t','e','m','M','a','n','u','f','a','c','t','u','r','e','r','E','n','g','l','i','s','h',0};
    static const WCHAR szSystemModelEnglish[] = {'s','z','S','y','s','t','e','m','M','o','d','e','l','E','n','g','l','i','s','h',0};
    static const WCHAR szBIOSEnglish[] = {'s','z','B','I','O','S','E','n','g','l','i','s','h',0};
    static const WCHAR szSetupParamEnglish[] = {'s','z','S','e','t','u','p','P','a','r','a','m','E','n','g','l','i','s','h',0};
    static const WCHAR szDxDiagVersion[] = {'s','z','D','x','D','i','a','g','V','e','r','s','i','o','n',0};

    static const WCHAR notpresentW[] = {'N','o','t',' ','p','r','e','s','e','n','t',0};

    static const WCHAR pagefile_fmtW[] = {'%','u','M','B',' ','u','s','e','d',',',' ','%','u','M','B',' ','a','v','a','i','l','a','b','l','e',0};
    static const WCHAR physmem_fmtW[] = {'%','u','M','B',' ','R','A','M',0};

    HRESULT hr;
    MEMORYSTATUSEX msex;
    OSVERSIONINFOW info;
    DWORD count, usedpage_mb, availpage_mb;
    WCHAR buffer[MAX_PATH], computer_name[MAX_COMPUTERNAME_LENGTH + 1], print_buf[200], localized_pagefile_fmt[200];
    DWORD_PTR args[2];

    hr = add_ui4_property(node, dwDirectXVersionMajor, 9);
    if (FAILED(hr))
        return hr;

    hr = add_ui4_property(node, dwDirectXVersionMinor, 0);
    if (FAILED(hr))
        return hr;

    hr = add_bstr_property(node, szDirectXVersionLetter, szDirectXVersionLetter_v);
    if (FAILED(hr))
        return hr;

    hr = add_bstr_property(node, szDirectXVersionEnglish, szDirectXVersionEnglish_v);
    if (FAILED(hr))
        return hr;

    hr = add_bstr_property(node, szDirectXVersionLongEnglish, szDirectXVersionLongEnglish_v);
    if (FAILED(hr))
        return hr;

    hr = add_bool_property(node, bDebug, FALSE);
    if (FAILED(hr))
        return hr;

    hr = add_bool_property(node, bNECPC98, FALSE);
    if (FAILED(hr))
        return hr;

    msex.dwLength = sizeof(msex);
    GlobalMemoryStatusEx(&msex);

    hr = add_ull_as_bstr_property(node, ullPhysicalMemory, msex.ullTotalPhys);
    if (FAILED(hr))
        return hr;

    hr = add_ull_as_bstr_property(node, ullUsedPageFile, msex.ullTotalPageFile - msex.ullAvailPageFile);
    if (FAILED(hr))
        return hr;

    hr = add_ull_as_bstr_property(node, ullAvailPageFile, msex.ullAvailPageFile);
    if (FAILED(hr))
        return hr;

    hr = add_bool_property(node, bNetMeetingRunning, is_netmeeting_running());
    if (FAILED(hr))
        return hr;

    info.dwOSVersionInfoSize = sizeof(info);
    GetVersionExW(&info);

    hr = add_ui4_property(node, dwOSMajorVersion, info.dwMajorVersion);
    if (FAILED(hr))
        return hr;

    hr = add_ui4_property(node, dwOSMinorVersion, info.dwMinorVersion);
    if (FAILED(hr))
        return hr;

    hr = add_ui4_property(node, dwOSBuildNumber, info.dwBuildNumber);
    if (FAILED(hr))
        return hr;

    hr = add_ui4_property(node, dwOSPlatformID, info.dwPlatformId);
    if (FAILED(hr))
        return hr;

    hr = add_bstr_property(node, szCSDVersion, info.szCSDVersion);
    if (FAILED(hr))
        return hr;

    /* FIXME: Roundoff should not be done with truncated division. */
    swprintf(print_buf, physmem_fmtW,
              (DWORD)(msex.ullTotalPhys / (1024 * 1024)));
    hr = add_bstr_property(node, szPhysicalMemoryEnglish, print_buf);
    if (FAILED(hr))
        return hr;

    usedpage_mb = (DWORD)((msex.ullTotalPageFile - msex.ullAvailPageFile) / (1024 * 1024));
    availpage_mb = (DWORD)(msex.ullAvailPageFile / (1024 * 1024));
    LoadStringW(dxdiagn_instance, IDS_PAGE_FILE_FORMAT, localized_pagefile_fmt,
                ARRAY_SIZE(localized_pagefile_fmt));
    args[0] = usedpage_mb;
    args[1] = availpage_mb;
    FormatMessageW(FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ARGUMENT_ARRAY, localized_pagefile_fmt,
                   0, 0, print_buf, ARRAY_SIZE(print_buf), (__ms_va_list*)args);

    hr = add_bstr_property(node, szPageFileLocalized, print_buf);
    if (FAILED(hr))
        return hr;

    swprintf(print_buf, pagefile_fmtW, usedpage_mb, availpage_mb);

    hr = add_bstr_property(node, szPageFileEnglish, print_buf);
    if (FAILED(hr))
        return hr;

    GetWindowsDirectoryW(buffer, MAX_PATH);

    hr = add_bstr_property(node, szWindowsDir, buffer);
    if (FAILED(hr))
        return hr;

    count = ARRAY_SIZE(computer_name);
    if (!GetComputerNameW(computer_name, &count))
        return E_FAIL;

    hr = add_bstr_property(node, szMachineNameLocalized, computer_name);
    if (FAILED(hr))
        return hr;

    hr = add_bstr_property(node, szMachineNameEnglish, computer_name);
    if (FAILED(hr))
        return hr;

    hr = add_bstr_property(node, szSystemManufacturerEnglish, szEmpty);
    if (FAILED(hr))
        return hr;

    hr = add_bstr_property(node, szSystemModelEnglish, szEmpty);
    if (FAILED(hr))
        return hr;

    hr = add_bstr_property(node, szBIOSEnglish, szEmpty);
    if (FAILED(hr))
        return hr;

    hr = fill_processor_information(node);
    if (FAILED(hr))
        return hr;

    hr = add_bstr_property(node, szSetupParamEnglish, notpresentW);
    if (FAILED(hr))
        return hr;

    hr = add_bstr_property(node, szDxDiagVersion, szEmpty);
    if (FAILED(hr))
        return hr;

    hr = fill_language_information(node);
    if (FAILED(hr))
        return hr;

    hr = fill_datetime_information(node);
    if (FAILED(hr))
        return hr;

    hr = fill_os_string_information(node, &info);
    if (FAILED(hr))
        return hr;

    return S_OK;
}