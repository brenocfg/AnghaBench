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
typedef  scalar_t__ uint32_t ;
struct vo {struct priv* priv; } ;
struct priv {scalar_t__ w; scalar_t__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ graphics_get_display_size (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int update_display_size(struct vo *vo)
{
    struct priv *p = vo->priv;

    uint32_t n_w = 0, n_h = 0;
    if (graphics_get_display_size(0, &n_w, &n_h) < 0) {
        MP_FATAL(vo, "Could not get display size.\n");
        return -1;
    }

    if (p->w == n_w && p->h == n_h)
        return 0;

    p->w = n_w;
    p->h = n_h;

    MP_VERBOSE(vo, "Display size: %dx%d\n", p->w, p->h);

    return 0;
}