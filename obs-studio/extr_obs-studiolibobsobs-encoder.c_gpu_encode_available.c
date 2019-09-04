#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int caps; } ;
struct obs_encoder {TYPE_1__ info; } ;
struct TYPE_5__ {scalar_t__ using_nv12_tex; } ;
struct TYPE_6__ {TYPE_2__ video; } ;

/* Variables and functions */
 int OBS_ENCODER_CAP_PASS_TEXTURE ; 
 TYPE_3__* obs ; 

__attribute__((used)) static inline bool gpu_encode_available(const struct obs_encoder *encoder)
{
    return (encoder->info.caps & OBS_ENCODER_CAP_PASS_TEXTURE) != 0 &&
		obs->video.using_nv12_tex;
}