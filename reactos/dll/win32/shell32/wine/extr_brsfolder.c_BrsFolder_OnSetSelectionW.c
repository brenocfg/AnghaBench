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
struct TYPE_4__ {int /*<<< orphan*/  hwndTreeView; } ;
typedef  TYPE_1__ browse_info ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HTREEITEM ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ BrsFolder_OnSetExpanded (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVGN_CARET ; 
 int /*<<< orphan*/  TVM_SELECTITEM ; 

__attribute__((used)) static BOOL BrsFolder_OnSetSelectionW(browse_info *info, LPVOID selection, BOOL is_str) {
    HTREEITEM hItem;
    BOOL bResult;

    if (!selection) return FALSE;

    bResult = BrsFolder_OnSetExpanded(info, selection, is_str, &hItem);
    if (bResult)
        SendMessageW(info->hwndTreeView, TVM_SELECTITEM, TVGN_CARET, (LPARAM)hItem );
    return bResult;
}