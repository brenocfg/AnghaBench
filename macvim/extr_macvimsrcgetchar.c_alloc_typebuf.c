#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ tb_change_cnt; scalar_t__ tb_no_abbr_cnt; scalar_t__ tb_silent; scalar_t__ tb_maplen; scalar_t__ tb_len; scalar_t__ tb_off; int /*<<< orphan*/  tb_buflen; int /*<<< orphan*/ * tb_noremap; int /*<<< orphan*/ * tb_buf; } ;

/* Variables and functions */
 int FAIL ; 
 int OK ; 
 int /*<<< orphan*/  TYPELEN_INIT ; 
 void* alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_typebuf () ; 
 TYPE_1__ typebuf ; 

int
alloc_typebuf()
{
    typebuf.tb_buf = alloc(TYPELEN_INIT);
    typebuf.tb_noremap = alloc(TYPELEN_INIT);
    if (typebuf.tb_buf == NULL || typebuf.tb_noremap == NULL)
    {
	free_typebuf();
	return FAIL;
    }
    typebuf.tb_buflen = TYPELEN_INIT;
    typebuf.tb_off = 0;
    typebuf.tb_len = 0;
    typebuf.tb_maplen = 0;
    typebuf.tb_silent = 0;
    typebuf.tb_no_abbr_cnt = 0;
    if (++typebuf.tb_change_cnt == 0)
	typebuf.tb_change_cnt = 1;
    return OK;
}