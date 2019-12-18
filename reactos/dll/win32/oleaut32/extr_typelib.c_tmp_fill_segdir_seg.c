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
struct TYPE_5__ {scalar_t__ len; } ;
typedef  TYPE_1__ WMSFT_SegContents ;
struct TYPE_6__ {int offset; int res08; int res0c; scalar_t__ length; } ;
typedef  TYPE_2__ MSFT_pSeg ;
typedef  int DWORD ;

/* Variables and functions */

__attribute__((used)) static void tmp_fill_segdir_seg(MSFT_pSeg *segdir, WMSFT_SegContents *contents, DWORD *running_offset)
{
    if(contents && contents->len){
        segdir->offset = *running_offset;
        segdir->length = contents->len;
        *running_offset += segdir->length;
    }else{
        segdir->offset = -1;
        segdir->length = 0;
    }

    /* TODO: do these ever change? */
    segdir->res08 = -1;
    segdir->res0c = 0xf;
}