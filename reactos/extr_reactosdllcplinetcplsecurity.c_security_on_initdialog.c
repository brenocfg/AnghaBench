#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int himages; int num_zones; int /*<<< orphan*/  zone_enumerator; int /*<<< orphan*/  zone_mgr; int /*<<< orphan*/ * zones; int /*<<< orphan*/ * levels; void* zone_attr; void* hlv; void* htb; int /*<<< orphan*/  hsec; } ;
typedef  TYPE_1__ secdlg_data ;
typedef  int /*<<< orphan*/  ZONEATTRIBUTES ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int INT_PTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DWLP_USER ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  EnableWindow (void*,int) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 void* GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_SEC_LISTVIEW ; 
 int /*<<< orphan*/  IDC_SEC_TRACKBAR ; 
 int /*<<< orphan*/  IInternetZoneManager_GetZoneAt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int ILC_COLOR32 ; 
 int ILC_MASK ; 
 int ImageList_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  LVM_SETIMAGELIST ; 
 int LVSIL_NORMAL ; 
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ NUM_TRACKBAR_POS ; 
 int /*<<< orphan*/  SM_CXICON ; 
 int /*<<< orphan*/  SM_CYICON ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBM_SETRANGE ; 
 int /*<<< orphan*/  TBM_SETTICFREQ ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int TRUE ; 
 scalar_t__ URLZONE_INTERNET ; 
 scalar_t__ URLZONE_INTRANET ; 
 scalar_t__ URLZONE_INVALID ; 
 scalar_t__ URLZONE_TRUSTED ; 
 scalar_t__ URLZONE_UNTRUSTED ; 
 int /*<<< orphan*/  add_zone_to_listview (TYPE_1__*,scalar_t__*,scalar_t__) ; 
 void* heap_alloc (int) ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  security_enum_zones (TYPE_1__*) ; 
 int /*<<< orphan*/  security_on_destroy (TYPE_1__*) ; 

__attribute__((used)) static INT_PTR security_on_initdialog(HWND hsec)
{
    secdlg_data *sd;
    HRESULT hr;
    DWORD current_zone;
    DWORD lv_index = 0;
    DWORD i;

    sd = heap_alloc_zero(sizeof(secdlg_data));
    SetWindowLongPtrW(hsec, DWLP_USER, (LONG_PTR) sd);
    if (!sd) {
        return FALSE;
    }

    sd->hsec = hsec;
    sd->hlv = GetDlgItem(hsec, IDC_SEC_LISTVIEW);
    sd->htb = GetDlgItem(hsec, IDC_SEC_TRACKBAR);

    EnableWindow(sd->htb, FALSE); /* not changeable yet */

    TRACE("(%p)   (data: %p, listview: %p, trackbar: %p)\n", hsec, sd, sd->hlv, sd->htb);

    SendMessageW(sd->htb, TBM_SETRANGE, FALSE, MAKELONG(0, NUM_TRACKBAR_POS - 1));
    SendMessageW(sd->htb, TBM_SETTICFREQ, 1, 0 );

    /* Create the image lists for the listview */
    sd->himages = ImageList_Create(GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), ILC_COLOR32 | ILC_MASK, 1, 1);

    TRACE("using imagelist: %p\n", sd->himages);
    if (!sd->himages) {
        ERR("ImageList_Create failed!\n");
        return FALSE;
    }
    SendMessageW(sd->hlv, LVM_SETIMAGELIST, LVSIL_NORMAL, (LPARAM)sd->himages);

    hr = security_enum_zones(sd);
    if (FAILED(hr)) {
        ERR("got 0x%x\n", hr);
        security_on_destroy(sd);
        return FALSE;
    }

    TRACE("found %d zones\n", sd->num_zones);

    /* remember ZONEATTRIBUTES for a listview entry */
    sd->zone_attr = heap_alloc(sizeof(ZONEATTRIBUTES) * sd->num_zones);
    if (!sd->zone_attr) {
        security_on_destroy(sd);
        return FALSE;
    }

    /* remember zone number and current security level for a listview entry */
    sd->zones = heap_alloc((sizeof(DWORD) + sizeof(DWORD)) * sd->num_zones);
    if (!sd->zones) {
        security_on_destroy(sd);
        return FALSE;
    }
    sd->levels = &sd->zones[sd->num_zones];

    /* use the same order as visible with native inetcpl.cpl */
    add_zone_to_listview(sd, &lv_index, URLZONE_INTERNET);
    add_zone_to_listview(sd, &lv_index, URLZONE_INTRANET);
    add_zone_to_listview(sd, &lv_index, URLZONE_TRUSTED);
    add_zone_to_listview(sd, &lv_index, URLZONE_UNTRUSTED);

    for (i = 0; i < sd->num_zones; i++)
    {
        hr = IInternetZoneManager_GetZoneAt(sd->zone_mgr, sd->zone_enumerator, i, &current_zone);
        if (SUCCEEDED(hr) && (current_zone != (DWORD)URLZONE_INVALID)) {
            if (!current_zone || (current_zone > URLZONE_UNTRUSTED)) {
                add_zone_to_listview(sd, &lv_index, current_zone);
            }
        }
    }
    return TRUE;
}