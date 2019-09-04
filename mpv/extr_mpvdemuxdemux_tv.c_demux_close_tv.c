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
typedef  int /*<<< orphan*/  tvi_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/ * priv; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tv_uninit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void demux_close_tv(demuxer_t *demuxer)
{
    tvi_handle_t *tvh=(tvi_handle_t*)(demuxer->priv);
    if (!tvh) return;
    tv_uninit(tvh);
    free(tvh);
    demuxer->priv=NULL;
}