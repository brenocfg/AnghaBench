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
struct vo {struct priv* priv; } ;
struct priv {TYPE_1__* kms; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct vo*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ USE_MASTER ; 
 int /*<<< orphan*/  crtc_setup (struct vo*) ; 
 scalar_t__ drmSetMaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acquire_vt(void *data)
{
    struct vo *vo = data;
    if (USE_MASTER) {
        struct priv *p = vo->priv;
        if (drmSetMaster(p->kms->fd)) {
            MP_WARN(vo, "Failed to acquire DRM master: %s\n", mp_strerror(errno));
        }
    }

    crtc_setup(vo);
}