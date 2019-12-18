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
struct vo {struct priv* priv; } ;
struct priv {scalar_t__ display; scalar_t__ update; int /*<<< orphan*/  display_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int /*<<< orphan*/  update_display_size (struct vo*) ; 
 int /*<<< orphan*/  vc_dispmanx_display_close (scalar_t__) ; 
 scalar_t__ vc_dispmanx_display_open (int /*<<< orphan*/ ) ; 
 scalar_t__ vc_dispmanx_update_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_vsync_callback (scalar_t__,int /*<<< orphan*/ ,struct vo*) ; 
 int /*<<< orphan*/  vsync_callback ; 

__attribute__((used)) static int recreate_dispmanx(struct vo *vo)
{
    struct priv *p = vo->priv;

    p->display = vc_dispmanx_display_open(p->display_nr);
    p->update = vc_dispmanx_update_start(0);
    if (!p->display || !p->update) {
        MP_FATAL(vo, "Could not get DISPMANX objects.\n");
        if (p->display)
            vc_dispmanx_display_close(p->display);
        p->display = 0;
        p->update = 0;
        return -1;
    }

    update_display_size(vo);

    vc_dispmanx_vsync_callback(p->display, vsync_callback, vo);

    return 0;
}