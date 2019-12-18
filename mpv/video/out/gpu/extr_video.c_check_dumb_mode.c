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
struct gl_video_opts {scalar_t__ dumb_mode; scalar_t__* user_shaders; TYPE_2__* scaler; scalar_t__ unsharp; scalar_t__ deband; scalar_t__ blend_subs; scalar_t__ interpolation; scalar_t__ sigmoid_upscaling; scalar_t__ linear_upscaling; scalar_t__ linear_downscaling; scalar_t__ correct_downscaling; } ;
struct gl_video {scalar_t__ use_integer_conversion; struct gl_video_opts opts; } ;
struct TYPE_3__ {char* name; } ;
struct TYPE_4__ {TYPE_1__ kernel; } ;

/* Variables and functions */
 int SCALER_COUNT ; 
 int SCALER_TSCALE ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static bool check_dumb_mode(struct gl_video *p)
{
    struct gl_video_opts *o = &p->opts;
    if (p->use_integer_conversion)
        return false;
    if (o->dumb_mode > 0) // requested by user
        return true;
    if (o->dumb_mode < 0) // disabled by user
        return false;

    // otherwise, use auto-detection
    if (o->correct_downscaling || o->linear_downscaling ||
        o->linear_upscaling || o->sigmoid_upscaling || o->interpolation ||
        o->blend_subs || o->deband || o->unsharp)
        return false;
    // check remaining scalers (tscale is already implicitly excluded above)
    for (int i = 0; i < SCALER_COUNT; i++) {
        if (i != SCALER_TSCALE) {
            const char *name = o->scaler[i].kernel.name;
            if (name && strcmp(name, "bilinear") != 0)
                return false;
        }
    }
    if (o->user_shaders && o->user_shaders[0])
        return false;
    return true;
}