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
struct mp_user_filter {int /*<<< orphan*/  last_in_aformat; int /*<<< orphan*/  name; int /*<<< orphan*/  last_in_vformat; struct chain* p; } ;
struct mp_image {int /*<<< orphan*/  params; } ;
struct mp_frame {scalar_t__ type; struct mp_image* data; } ;
struct mp_aframe {int /*<<< orphan*/  params; } ;
struct TYPE_2__ {int reconfig_happened; int /*<<< orphan*/  output_aformat; int /*<<< orphan*/  input_aformat; int /*<<< orphan*/  output_params; int /*<<< orphan*/  input_params; } ;
struct chain {TYPE_1__ public; struct mp_user_filter* output; struct mp_user_filter* input; } ;

/* Variables and functions */
 scalar_t__ MP_FRAME_AUDIO ; 
 scalar_t__ MP_FRAME_VIDEO ; 
 int /*<<< orphan*/  MP_VERBOSE (struct chain*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_aframe_config_copy (int /*<<< orphan*/ ,struct mp_image*) ; 
 int /*<<< orphan*/  mp_aframe_config_equals (struct mp_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_aframe_format_str (struct mp_image*) ; 
 int /*<<< orphan*/  mp_image_params_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_image_params_to_str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_output_caps (struct chain*) ; 

__attribute__((used)) static void check_in_format_change(struct mp_user_filter *u,
                                   struct mp_frame frame)
{
    struct chain *p = u->p;

    if (frame.type == MP_FRAME_VIDEO) {
        struct mp_image *img = frame.data;

        if (!mp_image_params_equal(&img->params, &u->last_in_vformat)) {
            MP_VERBOSE(p, "[%s] %s\n", u->name,
                       mp_image_params_to_str(&img->params));
            u->last_in_vformat = img->params;

            if (u == p->input) {
                p->public.input_params = img->params;

                // Unfortunately there's no good place to update these.
                // But a common case is enabling HW decoding, which
                // might init some support of them in the VO, and update
                // the VO's format list.
                update_output_caps(p);
            } else if (u == p->output) {
                p->public.output_params = img->params;
            }

            p->public.reconfig_happened = true;
        }
    }

    if (frame.type == MP_FRAME_AUDIO) {
        struct mp_aframe *aframe = frame.data;

        if (!mp_aframe_config_equals(aframe, u->last_in_aformat)) {
            MP_VERBOSE(p, "[%s] %s\n", u->name,
                       mp_aframe_format_str(aframe));
            mp_aframe_config_copy(u->last_in_aformat, aframe);

            if (u == p->input) {
                mp_aframe_config_copy(p->public.input_aformat, aframe);
            } else if (u == p->output) {
                mp_aframe_config_copy(p->public.output_aformat, aframe);
            }

            p->public.reconfig_happened = true;
        }
    }
}