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
struct vo {scalar_t__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int /*<<< orphan*/  MP_WARN (struct vo*,char*) ; 
 int /*<<< orphan*/  destroy_dispmanx (struct vo*) ; 
 scalar_t__ reconfig (struct vo*,scalar_t__) ; 
 int /*<<< orphan*/  recreate_dispmanx (struct vo*) ; 

__attribute__((used)) static void recreate_renderer(struct vo *vo)
{
    MP_WARN(vo, "Recreating renderer after display change.\n");

    destroy_dispmanx(vo);
    recreate_dispmanx(vo);

    if (vo->params) {
        if (reconfig(vo, vo->params) < 0)
            MP_FATAL(vo, "Recreation failed.\n");
    }
}