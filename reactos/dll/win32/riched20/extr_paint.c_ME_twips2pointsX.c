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
struct TYPE_5__ {int cx; } ;
struct TYPE_7__ {TYPE_2__* editor; TYPE_1__ dpi; } ;
struct TYPE_6__ {int nZoomNumerator; int nZoomDenominator; } ;
typedef  TYPE_3__ ME_Context ;

/* Variables and functions */

int ME_twips2pointsX(const ME_Context *c, int x)
{
  if (c->editor->nZoomNumerator == 0)
    return x * c->dpi.cx / 1440;
  else
    return x * c->dpi.cx * c->editor->nZoomNumerator / 1440 / c->editor->nZoomDenominator;
}