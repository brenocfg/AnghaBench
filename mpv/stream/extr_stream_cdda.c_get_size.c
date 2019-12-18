#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ stream_t ;
typedef  int int64_t ;
struct TYPE_5__ {int end_sector; int start_sector; } ;
typedef  TYPE_2__ cdda_priv ;

/* Variables and functions */
 int CDIO_CD_FRAMESIZE_RAW ; 

__attribute__((used)) static int64_t get_size(stream_t *st)
{
    cdda_priv *p = st->priv;
    return (p->end_sector + 1 - p->start_sector) * CDIO_CD_FRAMESIZE_RAW;
}