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
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HCERTSTORE ;

/* Variables and functions */
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_MGR_STORES ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCM_GETCURSEL ; 
 int /*<<< orphan*/  cert_mgr_index_to_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HCERTSTORE cert_mgr_current_store(HWND hwnd)
{
    HWND tab = GetDlgItem(hwnd, IDC_MGR_STORES);

    return cert_mgr_index_to_store(tab, SendMessageW(tab, TCM_GETCURSEL, 0, 0));
}