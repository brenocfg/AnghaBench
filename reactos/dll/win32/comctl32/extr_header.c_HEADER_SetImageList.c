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
struct TYPE_3__ {int /*<<< orphan*/  himl; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HIMAGELIST ;
typedef  TYPE_1__ HEADER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
HEADER_SetImageList (HEADER_INFO *infoPtr, HIMAGELIST himl)
{
    HIMAGELIST himlOld;

    TRACE("(himl %p)\n", himl);
    himlOld = infoPtr->himl;
    infoPtr->himl = himl;

    /* FIXME: Refresh needed??? */

    return (LRESULT)himlOld;
}