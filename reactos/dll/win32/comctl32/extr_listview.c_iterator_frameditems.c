#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  ITERATOR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  LISTVIEW_GetOrigin (int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  OffsetRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iterator_frameditems_absolute (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL iterator_frameditems(ITERATOR* i, const LISTVIEW_INFO* infoPtr, const RECT *lprc)
{
    RECT frame = *lprc;
    POINT Origin;

    TRACE("(lprc=%s)\n", wine_dbgstr_rect(lprc));

    LISTVIEW_GetOrigin(infoPtr, &Origin);
    OffsetRect(&frame, -Origin.x, -Origin.y);

    return iterator_frameditems_absolute(i, infoPtr, &frame);
}