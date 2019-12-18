#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  top; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct TYPE_6__ {int /*<<< orphan*/  top; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct TYPE_7__ {TYPE_1__ rcChannel; } ;
typedef  TYPE_2__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_3__* LPRECT ;

/* Variables and functions */

__attribute__((used)) static inline LRESULT
TRACKBAR_GetChannelRect (const TRACKBAR_INFO *infoPtr, LPRECT lprc)
{
    if (lprc == NULL) return 0;

    lprc->left   = infoPtr->rcChannel.left;
    lprc->right  = infoPtr->rcChannel.right;
    lprc->bottom = infoPtr->rcChannel.bottom;
    lprc->top    = infoPtr->rcChannel.top;

    return 0;
}