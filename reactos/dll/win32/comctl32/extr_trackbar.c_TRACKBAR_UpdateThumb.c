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
struct TYPE_4__ {int /*<<< orphan*/  rcThumb; int /*<<< orphan*/  lPos; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  TRACKBAR_CalcThumb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
TRACKBAR_UpdateThumb (TRACKBAR_INFO *infoPtr)
{
    TRACKBAR_CalcThumb(infoPtr, infoPtr->lPos, &infoPtr->rcThumb);
}