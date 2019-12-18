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
struct hierarchy_data {int /*<<< orphan*/  pCertViewInfo; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_VIEWCERTIFICATE ; 
 int /*<<< orphan*/  set_certificate_status_for_end_cert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_cert_chain (int /*<<< orphan*/ ,struct hierarchy_data*) ; 

__attribute__((used)) static void show_cert_hierarchy(HWND hwnd, struct hierarchy_data *data)
{
    /* Disable view certificate button until a certificate is selected */
    EnableWindow(GetDlgItem(hwnd, IDC_VIEWCERTIFICATE), FALSE);
    show_cert_chain(hwnd, data);
    set_certificate_status_for_end_cert(hwnd, data->pCertViewInfo);
}