#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  viewInfo ;
struct SelectCertData {int /*<<< orphan*/  rgPropSheetPages; int /*<<< orphan*/  cPropSheetPages; int /*<<< orphan*/  rghStores; int /*<<< orphan*/  cStores; int /*<<< orphan*/  callbackData; scalar_t__ (* displayProc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int dwSize; int /*<<< orphan*/  rgPropSheetPages; int /*<<< orphan*/  cPropSheetPages; int /*<<< orphan*/  rghStores; int /*<<< orphan*/  cStores; int /*<<< orphan*/  pCertContext; int /*<<< orphan*/  hwndParent; } ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ CRYPTUI_VIEWCERTIFICATE_STRUCTW ;

/* Variables and functions */
 int /*<<< orphan*/  CryptUIDlgViewCertificateW (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void select_cert_view(HWND hwnd, PCCERT_CONTEXT cert, struct SelectCertData *data)
{
    CRYPTUI_VIEWCERTIFICATE_STRUCTW viewInfo;

    if (data->displayProc && data->displayProc(cert, hwnd, data->callbackData))
        return;
    memset(&viewInfo, 0, sizeof(viewInfo));
    viewInfo.dwSize = sizeof(viewInfo);
    viewInfo.hwndParent = hwnd;
    viewInfo.pCertContext = cert;
    viewInfo.cStores = data->cStores;
    viewInfo.rghStores = data->rghStores;
    viewInfo.cPropSheetPages = data->cPropSheetPages;
    viewInfo.rgPropSheetPages = data->rgPropSheetPages;
    /* FIXME: this should be modal */
    CryptUIDlgViewCertificateW(&viewInfo, NULL);
}