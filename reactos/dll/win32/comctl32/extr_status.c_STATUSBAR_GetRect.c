#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bound; } ;
struct TYPE_7__ {size_t numParts; TYPE_2__* parts; TYPE_1__ part0; scalar_t__ simple; } ;
struct TYPE_6__ {int /*<<< orphan*/  bound; } ;
typedef  TYPE_3__ STATUS_INFO ;
typedef  int /*<<< orphan*/ * LPRECT ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
STATUSBAR_GetRect (const STATUS_INFO *infoPtr, INT nPart, LPRECT rect)
{
    TRACE("part %d\n", nPart);
    if(nPart >= infoPtr->numParts || nPart < 0)
      return FALSE;
    if (infoPtr->simple)
	*rect = infoPtr->part0.bound;
    else
	*rect = infoPtr->parts[nPart].bound;
    return TRUE;
}