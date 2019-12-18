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
struct ra_hwdec_mapper {TYPE_1__* owner; } ;
struct priv_owner {int /*<<< orphan*/  (* interop_uninit ) (struct ra_hwdec_mapper*) ;} ;
struct TYPE_2__ {struct priv_owner* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ra_hwdec_mapper*) ; 

__attribute__((used)) static void mapper_uninit(struct ra_hwdec_mapper *mapper)
{
    struct priv_owner *p_owner = mapper->owner->priv;
    if (p_owner->interop_uninit) {
        p_owner->interop_uninit(mapper);
    }
}