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
struct TYPE_7__ {TYPE_2__* cd; } ;
typedef  TYPE_3__ cdda_priv ;
struct TYPE_6__ {int tracks; TYPE_1__* disc_toc; } ;
struct TYPE_5__ {unsigned int dwStartSector; } ;

/* Variables and functions */

__attribute__((used)) static int get_track_by_sector(cdda_priv *p, unsigned int sector)
{
    int i;
    for (i = p->cd->tracks; i >= 0; --i)
        if (p->cd->disc_toc[i].dwStartSector <= sector)
            break;
    return i;
}