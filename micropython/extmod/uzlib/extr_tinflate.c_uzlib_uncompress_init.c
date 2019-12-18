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
struct TYPE_3__ {int btype; unsigned int dict_size; scalar_t__ curlen; scalar_t__ dict_idx; void* dict_ring; scalar_t__ bfinal; scalar_t__ bitcount; scalar_t__ eof; } ;
typedef  TYPE_1__ TINF_DATA ;

/* Variables and functions */

void uzlib_uncompress_init(TINF_DATA *d, void *dict, unsigned int dictLen)
{
   d->eof = 0;
   d->bitcount = 0;
   d->bfinal = 0;
   d->btype = -1;
   d->dict_size = dictLen;
   d->dict_ring = dict;
   d->dict_idx = 0;
   d->curlen = 0;
}