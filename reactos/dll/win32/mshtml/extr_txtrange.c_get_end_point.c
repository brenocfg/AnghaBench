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
typedef  int /*<<< orphan*/  rangepoint_t ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
struct TYPE_3__ {int /*<<< orphan*/  nsrange; } ;
typedef  int /*<<< orphan*/  LONG ;
typedef  TYPE_1__ HTMLTxtRange ;

/* Variables and functions */
 int /*<<< orphan*/  init_rangepoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMRange_GetEndContainer (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMRange_GetEndOffset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_end_point(HTMLTxtRange *This, rangepoint_t *ret)
{
    nsIDOMNode *node;
    LONG off;

    nsIDOMRange_GetEndContainer(This->nsrange, &node);
    nsIDOMRange_GetEndOffset(This->nsrange, &off);

    init_rangepoint(ret, node, off);

    nsIDOMNode_Release(node);
}