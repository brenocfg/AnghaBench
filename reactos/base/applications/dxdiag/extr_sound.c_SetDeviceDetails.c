#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  waveOut ;
typedef  int /*<<< orphan*/  szText ;
typedef  int WCHAR ;
struct TYPE_9__ {scalar_t__ wPid; scalar_t__ wMid; int cbSize; int /*<<< orphan*/  szPname; } ;
typedef  TYPE_1__ WAVEOUTCAPSW ;
typedef  int UINT ;
typedef  TYPE_1__ SP_DEVINFO_DATA ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ MMRESULT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPCGUID ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  InfoData ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HDEVINFO ;
typedef  int DWORD ;

/* Variables and functions */
 int DIGCF_PRESENT ; 
 int DIGCF_PROFILE ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 int /*<<< orphan*/  EnumerateDrivers (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  IDC_STATIC_ADAPTER_PROVIDER ; 
 int /*<<< orphan*/  IDC_STATIC_DSOUND_DATE ; 
 int /*<<< orphan*/  IDC_STATIC_DSOUND_DEVICEID ; 
 int /*<<< orphan*/  IDC_STATIC_DSOUND_DRIVER ; 
 int /*<<< orphan*/  IDC_STATIC_DSOUND_PRODUCTID ; 
 int /*<<< orphan*/  IDC_STATIC_DSOUND_STANDARD ; 
 int /*<<< orphan*/  IDC_STATIC_DSOUND_TYPE ; 
 int /*<<< orphan*/  IDC_STATIC_DSOUND_VENDORID ; 
 int /*<<< orphan*/  IDC_STATIC_DSOUND_VERSION ; 
 int /*<<< orphan*/  IDS_OPTION_NO ; 
 int /*<<< orphan*/  IDS_OPTION_YES ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  MAXPNAMELEN ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 scalar_t__ MM_MSFT_WDMAUDIO_WAVEOUT ; 
 int /*<<< orphan*/  SPDRP_MFG ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupDiDestroyDeviceInfoList (scalar_t__) ; 
 scalar_t__ SetupDiEnumDeviceInfo (scalar_t__,int,TYPE_1__*) ; 
 scalar_t__ SetupDiGetClassDevsW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SetupDiGetDeviceInstanceId (scalar_t__,TYPE_1__*,int*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupDiGetDeviceRegistryPropertyW (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ waveOutGetDevCapsW (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int waveOutGetNumDevs () ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcsncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
SetDeviceDetails(HWND hwndDlg, LPCGUID classGUID, LPCWSTR lpcstrDescription)
{
    HDEVINFO hInfo;
    DWORD dwIndex = 0;
    SP_DEVINFO_DATA InfoData;
    WCHAR szText[30];
    HWND hDlgCtrls[3];
    WAVEOUTCAPSW waveOut;
    UINT numDev;
    MMRESULT errCode;


    /*  enumerate waveout devices */
    numDev = waveOutGetNumDevs();
    if (numDev)
    {
        do
        {
                ZeroMemory(&waveOut, sizeof(waveOut));
                errCode = waveOutGetDevCapsW(dwIndex++, &waveOut, sizeof(waveOut));
                if (!wcsncmp(lpcstrDescription, waveOut.szPname, min(MAXPNAMELEN, wcslen(waveOut.szPname))))
                {
                    /* set the product id */
                    SetDlgItemInt(hwndDlg, IDC_STATIC_DSOUND_PRODUCTID, waveOut.wPid, FALSE);
                    /* set the vendor id */
                    SetDlgItemInt(hwndDlg, IDC_STATIC_DSOUND_VENDORID, waveOut.wMid, FALSE);
                    /* check if it's a WDM audio driver */
                    if (waveOut.wPid == MM_MSFT_WDMAUDIO_WAVEOUT)
                        SendDlgItemMessageW(hwndDlg, IDC_STATIC_DSOUND_TYPE, WM_SETTEXT, 0, (LPARAM)L"WDM");

                    /* check if device is default device */
                    szText[0] = L'\0';
                    if (dwIndex - 1 == 0) /* FIXME assume default playback device is device 0 */
                        LoadStringW(hInst, IDS_OPTION_YES, szText, sizeof(szText)/sizeof(WCHAR));
                    else
                        LoadStringW(hInst, IDS_OPTION_NO, szText, sizeof(szText)/sizeof(WCHAR));

                    szText[(sizeof(szText)/sizeof(WCHAR))-1] = L'\0';
                    /* set default device info */
                    SendDlgItemMessageW(hwndDlg, IDC_STATIC_DSOUND_STANDARD, WM_SETTEXT, 0, (LPARAM)szText);
                    break;
                }
                }while(errCode == MMSYSERR_NOERROR && dwIndex < numDev);
    }

    dwIndex = 0;
    /* create the setup list */
    hInfo = SetupDiGetClassDevsW(classGUID, NULL, NULL, DIGCF_PRESENT|DIGCF_PROFILE);
    if (hInfo == INVALID_HANDLE_VALUE)
        return;

    do
    {
        ZeroMemory(&InfoData, sizeof(InfoData));
        InfoData.cbSize = sizeof(InfoData);

        if (SetupDiEnumDeviceInfo(hInfo, dwIndex, &InfoData))
        {
            /* set device name */
            if (SetupDiGetDeviceInstanceId(hInfo, &InfoData, szText, sizeof(szText)/sizeof(WCHAR), NULL))
                SendDlgItemMessageW(hwndDlg, IDC_STATIC_DSOUND_DEVICEID, WM_SETTEXT, 0, (LPARAM)szText);

            /* set the manufacturer name */
            if (SetupDiGetDeviceRegistryPropertyW(hInfo, &InfoData, SPDRP_MFG, NULL, (PBYTE)szText, sizeof(szText), NULL))
                SendDlgItemMessageW(hwndDlg, IDC_STATIC_ADAPTER_PROVIDER, WM_SETTEXT, 0, (LPARAM)szText);

            /* FIXME
             * we currently enumerate only the first adapter 
             */
            hDlgCtrls[0] = GetDlgItem(hwndDlg, IDC_STATIC_DSOUND_DRIVER);
            hDlgCtrls[1] = GetDlgItem(hwndDlg, IDC_STATIC_DSOUND_VERSION);
            hDlgCtrls[2] = GetDlgItem(hwndDlg, IDC_STATIC_DSOUND_DATE);
            EnumerateDrivers(hDlgCtrls, hInfo, &InfoData);
            break;
        }

        if (GetLastError() == ERROR_NO_MORE_ITEMS)
            break;

        dwIndex++;
    }while(TRUE);

    /* destroy the setup list */
    SetupDiDestroyDeviceInfoList(hInfo);
}