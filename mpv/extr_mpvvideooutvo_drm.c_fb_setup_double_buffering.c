#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vo {struct priv* priv; } ;
struct priv {TYPE_4__* bufs; TYPE_3__* kms; scalar_t__ front_buf; } ;
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct TYPE_7__ {TYPE_1__ mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  fd; TYPE_2__ mode; } ;

/* Variables and functions */
 unsigned int BUF_COUNT ; 
 int /*<<< orphan*/  MP_ERR (struct vo*,char*) ; 
 int /*<<< orphan*/  fb_destroy (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  fb_setup_single (struct vo*,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static bool fb_setup_double_buffering(struct vo *vo)
{
    struct priv *p = vo->priv;

    p->front_buf = 0;
    for (unsigned int i = 0; i < 2; i++) {
        p->bufs[i].width = p->kms->mode.mode.hdisplay;
        p->bufs[i].height = p->kms->mode.mode.vdisplay;
    }

    for (unsigned int i = 0; i < BUF_COUNT; i++) {
        if (!fb_setup_single(vo, p->kms->fd, &p->bufs[i])) {
            MP_ERR(vo, "Cannot create framebuffer\n");
            for (unsigned int j = 0; j < i; j++) {
                fb_destroy(p->kms->fd, &p->bufs[j]);
            }
            return false;
        }
    }

    return true;
}