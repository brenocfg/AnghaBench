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
struct vdp_functions {scalar_t__ (* video_mixer_set_attribute_values ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void const**) ;int /*<<< orphan*/  (* get_error_string ) (scalar_t__) ;} ;
struct mp_vdpau_mixer {int /*<<< orphan*/  video_mixer; TYPE_1__* ctx; } ;
typedef  int /*<<< orphan*/  VdpVideoMixerAttribute ;
typedef  scalar_t__ VdpStatus ;
struct TYPE_2__ {struct vdp_functions vdp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct mp_vdpau_mixer*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ VDP_STATUS_OK ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void const**) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 

__attribute__((used)) static int set_video_attribute(struct mp_vdpau_mixer *mixer,
                               VdpVideoMixerAttribute attr,
                               const void *value, char *attr_name)
{
    struct vdp_functions *vdp = &mixer->ctx->vdp;
    VdpStatus vdp_st;

    vdp_st = vdp->video_mixer_set_attribute_values(mixer->video_mixer, 1,
                                                   &attr, &value);
    if (vdp_st != VDP_STATUS_OK) {
        MP_ERR(mixer, "Error setting video mixer attribute %s: %s\n", attr_name,
               vdp->get_error_string(vdp_st));
        return -1;
    }
    return 0;
}