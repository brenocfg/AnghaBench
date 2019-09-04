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
struct priv {int playing; int /*<<< orphan*/  hdl; scalar_t__ delay; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct ao*,char*) ; 
 int /*<<< orphan*/  MP_WARN (struct ao*,char*) ; 
 int /*<<< orphan*/  sio_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset(struct ao *ao)
{
    struct priv *p = ao->priv;

    if (p->playing) {
        MP_WARN(ao, "Blocking until remaining audio is played... (sndio design bug).\n");

        p->playing = false;

        if (!sio_stop(p->hdl))
            MP_ERR(ao, "reset: couldn't stop\n");
        p->delay = 0;
        if (!sio_start(p->hdl))
            MP_ERR(ao, "reset: couldn't start\n");
    }
}