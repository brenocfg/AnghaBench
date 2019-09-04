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
struct vo {struct priv* priv; } ;
struct priv {int pflip_happening; size_t front_buf; int /*<<< orphan*/  ev; TYPE_2__* kms; TYPE_1__* bufs; int /*<<< orphan*/  active; } ;
struct pollfd {int events; int revents; int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  crtc_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  fb; } ;

/* Variables and functions */
 size_t BUF_COUNT ; 
 int /*<<< orphan*/  DRM_MODE_PAGE_FLIP_EVENT ; 
 int /*<<< orphan*/  MP_ERR (struct vo*,char*,int) ; 
 int /*<<< orphan*/  MP_WARN (struct vo*,char*,int /*<<< orphan*/ ) ; 
 int POLLIN ; 
 int drmHandleEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drmModePageFlip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct priv*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int const) ; 

__attribute__((used)) static void flip_page(struct vo *vo)
{
    struct priv *p = vo->priv;
    if (!p->active || p->pflip_happening)
        return;

    int ret = drmModePageFlip(p->kms->fd, p->kms->crtc_id,
                              p->bufs[p->front_buf].fb,
                              DRM_MODE_PAGE_FLIP_EVENT, p);
    if (ret) {
        MP_WARN(vo, "Failed to queue page flip: %s\n", mp_strerror(errno));
    } else {
        p->front_buf++;
        p->front_buf %= BUF_COUNT;
        p->pflip_happening = true;
    }

    // poll page flip finish event
    const int timeout_ms = 3000;
    struct pollfd fds[1] = {
        { .events = POLLIN, .fd = p->kms->fd },
    };
    poll(fds, 1, timeout_ms);
    if (fds[0].revents & POLLIN) {
        ret = drmHandleEvent(p->kms->fd, &p->ev);
        if (ret != 0) {
            MP_ERR(vo, "drmHandleEvent failed: %i\n", ret);
            return;
        }
    }
}