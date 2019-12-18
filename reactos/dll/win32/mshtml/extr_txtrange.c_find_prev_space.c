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
struct TYPE_6__ {int /*<<< orphan*/  off; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ rangepoint_t ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free_rangepoint (TYPE_1__*) ; 
 int /*<<< orphan*/  init_rangepoint (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isspaceW (scalar_t__) ; 
 scalar_t__ move_prev_char (TYPE_1__*) ; 

__attribute__((used)) static LONG find_prev_space(rangepoint_t *iter, BOOL first_space)
{
    rangepoint_t prev;
    WCHAR c;

    init_rangepoint(&prev, iter->node, iter->off);
    c = move_prev_char(&prev);
    if(!c || (first_space && isspaceW(c)))
        return FALSE;

    do {
        free_rangepoint(iter);
        init_rangepoint(iter, prev.node, prev.off);
        c = move_prev_char(&prev);
    }while(c && !isspaceW(c));

    free_rangepoint(&prev);
    return TRUE;
}