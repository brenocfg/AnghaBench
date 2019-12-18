#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vo {struct priv* priv; } ;
struct priv {int active; TYPE_4__* kms; TYPE_1__* cur_fb; int /*<<< orphan*/  old_crtc; } ;
struct TYPE_7__ {int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {TYPE_3__ mode; TYPE_2__* connector; int /*<<< orphan*/  crtc_id; int /*<<< orphan*/  fd; } ;
struct TYPE_6__ {int /*<<< orphan*/  connector_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  drmModeGetCrtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drmModeSetCrtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool crtc_setup(struct vo *vo)
{
    struct priv *p = vo->priv;
    if (p->active)
        return true;
    p->old_crtc = drmModeGetCrtc(p->kms->fd, p->kms->crtc_id);
    int ret = drmModeSetCrtc(p->kms->fd, p->kms->crtc_id,
                             p->cur_fb->fb,
                             0, 0, &p->kms->connector->connector_id, 1,
                             &p->kms->mode.mode);
    p->active = true;
    return ret == 0;
}