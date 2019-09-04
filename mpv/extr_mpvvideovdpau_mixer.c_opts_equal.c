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
struct mp_vdpau_mixer_opts {scalar_t__ deint; scalar_t__ chroma_deint; scalar_t__ pullup; scalar_t__ hqscaling; scalar_t__ sharpen; scalar_t__ denoise; } ;

/* Variables and functions */

__attribute__((used)) static bool opts_equal(const struct mp_vdpau_mixer_opts *a,
                       const struct mp_vdpau_mixer_opts *b)
{
    return a->deint == b->deint && a->chroma_deint == b->chroma_deint &&
           a->pullup == b->pullup && a->hqscaling == b->hqscaling &&
           a->sharpen == b->sharpen && a->denoise == b->denoise;
}