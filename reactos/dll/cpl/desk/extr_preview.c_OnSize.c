#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {void* bottom; void* right; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_6__ {TYPE_1__ rcDesktop; } ;
typedef  TYPE_2__* PPREVIEW_DATA ;
typedef  void* INT ;

/* Variables and functions */
 int /*<<< orphan*/  CalculateItemSize (TYPE_2__*) ; 

__attribute__((used)) static VOID
OnSize(INT cx, INT cy, PPREVIEW_DATA pPreviewData)
{
    /* Get Desktop rectangle */
    pPreviewData->rcDesktop.left = 0;
    pPreviewData->rcDesktop.top = 0;
    pPreviewData->rcDesktop.right = cx;
    pPreviewData->rcDesktop.bottom = cy;

    CalculateItemSize(pPreviewData);
}