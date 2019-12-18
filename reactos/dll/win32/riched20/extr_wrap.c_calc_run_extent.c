#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nFlags; scalar_t__ nWidth; int /*<<< orphan*/  nDescent; int /*<<< orphan*/  nAscent; int /*<<< orphan*/  len; } ;
struct TYPE_6__ {scalar_t__ cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__ ME_Run ;
typedef  int /*<<< orphan*/  ME_Paragraph ;
typedef  int /*<<< orphan*/  ME_Context ;

/* Variables and functions */
 int MERF_HIDDEN ; 
 TYPE_1__ ME_GetRunSizeCommon (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void calc_run_extent(ME_Context *c, const ME_Paragraph *para, int startx, ME_Run *run)
{
    if (run->nFlags & MERF_HIDDEN) run->nWidth = 0;
    else
    {
        SIZE size = ME_GetRunSizeCommon( c, para, run, run->len, startx, &run->nAscent, &run->nDescent );
        run->nWidth = size.cx;
    }
}