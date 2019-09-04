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
struct mp_image {int dummy; } ;
struct get_image_cmd {int imgfmt; int w; int h; int stride_align; struct mp_image* res; struct dr_helper* dr; } ;
struct dr_helper {int /*<<< orphan*/  dispatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_dispatch_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct get_image_cmd*) ; 
 int /*<<< orphan*/  sync_get_image ; 

struct mp_image *dr_helper_get_image(struct dr_helper *dr, int imgfmt,
                                     int w, int h, int stride_align)
{
    struct get_image_cmd cmd = {
        .dr = dr,
        .imgfmt = imgfmt, .w = w, .h = h, .stride_align = stride_align,
    };
    mp_dispatch_run(dr->dispatch, sync_get_image, &cmd);
    return cmd.res;
}