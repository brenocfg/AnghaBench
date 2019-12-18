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
struct TYPE_5__ {int /*<<< orphan*/  hIcon; } ;
struct TYPE_7__ {int numParts; TYPE_2__* parts; TYPE_1__ part0; } ;
struct TYPE_6__ {int /*<<< orphan*/  hIcon; } ;
typedef  TYPE_3__ STATUS_INFO ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HICON ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int) ; 

__attribute__((used)) static HICON
STATUSBAR_GetIcon (const STATUS_INFO *infoPtr, INT nPart)
{
    TRACE("%d\n", nPart);
    /* MSDN says: "simple parts are indexed with -1" */
    if ((nPart < -1) || (nPart >= infoPtr->numParts))
	return 0;

    if (nPart == -1)
        return (infoPtr->part0.hIcon);
    else
        return (infoPtr->parts[nPart].hIcon);
}