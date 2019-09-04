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
struct MPContext {scalar_t__ playback_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPSEEK_EXACT ; 
 int /*<<< orphan*/  issue_refresh_seek (struct MPContext*,int /*<<< orphan*/ ) ; 
 scalar_t__ reinit_complex_filters (struct MPContext*,int) ; 

void update_lavfi_complex(struct MPContext *mpctx)
{
    if (mpctx->playback_initialized) {
        if (reinit_complex_filters(mpctx, false) != 0)
            issue_refresh_seek(mpctx, MPSEEK_EXACT);
    }
}