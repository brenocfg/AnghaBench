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
struct TYPE_4__ {int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  NMHDR ;
typedef  TYPE_1__ LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  IsWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_hdr (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline BOOL notify(const LISTVIEW_INFO *infoPtr, INT code)
{
    NMHDR nmh;
    HWND hwnd = infoPtr->hwndSelf;
    notify_hdr(infoPtr, code, &nmh);
    return IsWindow(hwnd);
}