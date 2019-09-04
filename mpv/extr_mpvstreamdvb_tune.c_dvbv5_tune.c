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
struct dtv_properties {int num; TYPE_2__* props; } ;
typedef  int /*<<< orphan*/  dvb_priv_t ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ u; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_SET_PROPERTY ; 
 int /*<<< orphan*/  MP_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  get_dvb_delsys (unsigned int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct dtv_properties*) ; 

__attribute__((used)) static int dvbv5_tune(dvb_priv_t *priv, int fd_frontend,
                       unsigned int delsys, struct dtv_properties* cmdseq)
{
    MP_VERBOSE(priv, "Tuning via S2API, channel is %s.\n",
               get_dvb_delsys(delsys));
    MP_VERBOSE(priv, "Dumping raw tuning commands and values:\n");
    for (int i = 0; i < cmdseq->num; ++i) {
        MP_VERBOSE(priv, "%02d: 0x%x(%d) => 0x%x(%d)\n",
                   i, cmdseq->props[i].cmd, cmdseq->props[i].cmd,
                   cmdseq->props[i].u.data, cmdseq->props[i].u.data);
    }
    if (ioctl(fd_frontend, FE_SET_PROPERTY, cmdseq) < 0) {
        MP_ERR(priv, "ERROR tuning channel\n");
        return -1;
    }
    return 0;
}