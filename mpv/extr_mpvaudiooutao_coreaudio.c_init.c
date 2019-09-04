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
struct priv {int /*<<< orphan*/  device; scalar_t__ change_physical_format; } ;
struct ao {int init_flags; char* redirect; int /*<<< orphan*/  format; struct priv* priv; } ;
typedef  int /*<<< orphan*/  AudioStreamBasicDescription ;

/* Variables and functions */
 int AO_INIT_EXCLUSIVE ; 
 int CONTROL_ERROR ; 
 int CONTROL_OK ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*) ; 
 int /*<<< orphan*/  af_fmt_is_pcm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ca_fill_asbd (struct ao*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ca_init_chmap (struct ao*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_audiounit (struct ao*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_physical_format (struct ao*) ; 
 int /*<<< orphan*/  reinit_device (struct ao*) ; 

__attribute__((used)) static int init(struct ao *ao)
{
    struct priv *p = ao->priv;

    if (!af_fmt_is_pcm(ao->format) || (ao->init_flags & AO_INIT_EXCLUSIVE)) {
        MP_VERBOSE(ao, "redirecting to coreaudio_exclusive\n");
        ao->redirect = "coreaudio_exclusive";
        return CONTROL_ERROR;
    }

    if (!reinit_device(ao))
        goto coreaudio_error;

    if (p->change_physical_format)
        init_physical_format(ao);

    if (!ca_init_chmap(ao, p->device))
        goto coreaudio_error;

    AudioStreamBasicDescription asbd;
    ca_fill_asbd(ao, &asbd);

    if (!init_audiounit(ao, asbd))
        goto coreaudio_error;

    return CONTROL_OK;

coreaudio_error:
    return CONTROL_ERROR;
}