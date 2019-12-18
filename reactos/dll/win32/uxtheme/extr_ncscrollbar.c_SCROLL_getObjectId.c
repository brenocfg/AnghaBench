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
typedef  int /*<<< orphan*/  LONG ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OBJID_HSCROLL ; 
 int /*<<< orphan*/  OBJID_VSCROLL ; 
#define  SB_HORZ 129 
#define  SB_VERT 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LONG SCROLL_getObjectId(INT nBar)
{
    switch(nBar)
    {
    case SB_HORZ:
        return OBJID_HSCROLL;
    case SB_VERT:
        return OBJID_VSCROLL;
    default:
        assert(FALSE);
        return 0;
    }
}