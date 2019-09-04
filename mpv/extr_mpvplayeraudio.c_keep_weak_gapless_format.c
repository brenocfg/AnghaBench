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
struct mp_aframe {int dummy; } ;

/* Variables and functions */
 scalar_t__ INT_MIN ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ af_format_conversion_score (int,int) ; 
 int mp_aframe_config_equals (struct mp_aframe*,struct mp_aframe*) ; 
 int mp_aframe_get_format (struct mp_aframe*) ; 
 struct mp_aframe* mp_aframe_new_ref (struct mp_aframe*) ; 
 int /*<<< orphan*/  mp_aframe_set_format (struct mp_aframe*,int) ; 
 int /*<<< orphan*/  talloc_free (struct mp_aframe*) ; 

__attribute__((used)) static bool keep_weak_gapless_format(struct mp_aframe *old, struct mp_aframe* new)
{
    bool res = false;
    struct mp_aframe *new_mod = mp_aframe_new_ref(new);
    if (!new_mod)
        abort();

    // If the sample formats are compatible (== libswresample generally can
    // convert them), keep the AO. On other changes, recreate it.

    int old_fmt = mp_aframe_get_format(old);
    int new_fmt = mp_aframe_get_format(new);

    if (af_format_conversion_score(old_fmt, new_fmt) == INT_MIN)
        goto done; // completely incompatible formats

    if (!mp_aframe_set_format(new_mod, old_fmt))
        goto done;

    res = mp_aframe_config_equals(old, new_mod);

done:
    talloc_free(new_mod);
    return res;
}