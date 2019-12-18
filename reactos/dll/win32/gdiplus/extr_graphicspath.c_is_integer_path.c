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
struct TYPE_6__ {int Count; TYPE_1__* Points; } ;
struct TYPE_7__ {TYPE_2__ pathdata; } ;
struct TYPE_5__ {scalar_t__ X; scalar_t__ Y; } ;
typedef  scalar_t__ REAL ;
typedef  TYPE_3__ GpPath ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 short gdip_round (scalar_t__) ; 

__attribute__((used)) static BOOL is_integer_path(const GpPath *path)
{
    int i;

    if (!path->pathdata.Count) return FALSE;

    for (i = 0; i < path->pathdata.Count; i++)
    {
        short x, y;
        x = gdip_round(path->pathdata.Points[i].X);
        y = gdip_round(path->pathdata.Points[i].Y);
        if (path->pathdata.Points[i].X != (REAL)x || path->pathdata.Points[i].Y != (REAL)y)
            return FALSE;
    }
    return TRUE;
}