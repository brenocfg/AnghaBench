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
typedef  int /*<<< orphan*/  LOGBRUSH ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  GpBrush ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBrushIndirect (int /*<<< orphan*/ *) ; 
 scalar_t__ Ok ; 
 scalar_t__ create_gdi_logbrush (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_gdi_logbrush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HBRUSH create_gdi_brush(const GpBrush *brush)
{
    LOGBRUSH lb;
    HBRUSH gdibrush;

    if (create_gdi_logbrush(brush, &lb) != Ok) return 0;

    gdibrush = CreateBrushIndirect(&lb);
    free_gdi_logbrush(&lb);

    return gdibrush;
}