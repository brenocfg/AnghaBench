#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* device; int /*<<< orphan*/ * hdl; } ;
struct TYPE_7__ {TYPE_1__ sndio; } ;
typedef  TYPE_2__ audio_in_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  SIO_REC ; 
 int ai_sndio_setup (TYPE_2__*) ; 
 int /*<<< orphan*/ * sio_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ai_sndio_init(audio_in_t *ai)
{
    int err;

    const char *device = ai->sndio.device;
    if (!device)
        device = "default";
    if ((ai->sndio.hdl = sio_open(device, SIO_REC, 0)) == NULL) {
        MP_ERR(ai, "could not open sndio audio");
        return -1;
    }

    err = ai_sndio_setup(ai);

    return err;
}