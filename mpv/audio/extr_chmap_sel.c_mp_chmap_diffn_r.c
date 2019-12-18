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
struct mp_chmap {int dummy; } ;

/* Variables and functions */
 int INT_MAX ; 
 scalar_t__ MP_ARRAY_SIZE (scalar_t__*) ; 
 struct mp_chmap MP_CHMAP_INIT_MONO ; 
 struct mp_chmap MP_CHMAP_INIT_STEREO ; 
 int mp_chmap_diffn (struct mp_chmap*,struct mp_chmap const*) ; 
 scalar_t__ mp_chmap_equals (struct mp_chmap*,struct mp_chmap const*) ; 
 int /*<<< orphan*/  replace_speakers (struct mp_chmap*,struct mp_chmap*) ; 
 scalar_t__* speaker_replacements ; 

__attribute__((used)) static int mp_chmap_diffn_r(const struct mp_chmap *a, const struct mp_chmap *b)
{
    int mindiff = INT_MAX;

    for (int i = -1; i < (int)MP_ARRAY_SIZE(speaker_replacements); i++) {
        struct mp_chmap ar = *a;
        if (i >= 0) {
            struct mp_chmap *r = (struct mp_chmap *)speaker_replacements[i];
            if (!replace_speakers(&ar, r))
                continue;
        }
        int d = mp_chmap_diffn(&ar, b);
        if (d < mindiff)
            mindiff = d;
    }

    // Special-case: we consider stereo a replacement for mono. (This is not
    // true in the other direction. Also, fl-fr is generally not a replacement
    // for fc. Thus it's not part of the speaker replacement list.)
    struct mp_chmap mono   = MP_CHMAP_INIT_MONO;
    struct mp_chmap stereo = MP_CHMAP_INIT_STEREO;
    if (mp_chmap_equals(&mono, b) && mp_chmap_equals(&stereo, a))
        mindiff = 0;

    return mindiff;
}