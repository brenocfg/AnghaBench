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
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LPNMLISTVIEW ;
typedef  int /*<<< orphan*/  LPNMHDR ;
typedef  int /*<<< orphan*/  LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugnmlistview (scalar_t__) ; 
 int /*<<< orphan*/  notify_hdr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline LRESULT notify_listview(const LISTVIEW_INFO *infoPtr, INT code, LPNMLISTVIEW plvnm)
{
    TRACE("(code=%d, plvnm=%s)\n", code, debugnmlistview(plvnm));
    return notify_hdr(infoPtr, code, (LPNMHDR)plvnm);
}