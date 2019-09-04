#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;
struct kms {TYPE_2__* connector; TYPE_1__ mode; } ;
struct TYPE_4__ {unsigned int count_modes; int /*<<< orphan*/ * modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct kms*,char*,int) ; 

__attribute__((used)) static bool setup_mode_by_idx(struct kms *kms, unsigned int mode_idx)
{
    if (mode_idx >= kms->connector->count_modes) {
        MP_ERR(kms, "Bad mode index (max = %d).\n",
               kms->connector->count_modes - 1);
        return false;
    }

    kms->mode.mode = kms->connector->modes[mode_idx];
    return true;
}