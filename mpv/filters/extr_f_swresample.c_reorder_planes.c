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
typedef  int /*<<< orphan*/  uint8_t ;
struct mp_chmap {scalar_t__* speaker; } ;
struct mp_aframe {int dummy; } ;

/* Variables and functions */
 int MP_NUM_CHANNELS ; 
 scalar_t__ MP_SPEAKER_ID_NA ; 
 int /*<<< orphan*/  af_fill_silence (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ ** mp_aframe_get_data_rw (struct mp_aframe*) ; 
 int /*<<< orphan*/  mp_aframe_get_format (struct mp_aframe*) ; 
 int mp_aframe_get_planes (struct mp_aframe*) ; 
 int mp_aframe_get_size (struct mp_aframe*) ; 
 int mp_aframe_get_sstride (struct mp_aframe*) ; 
 int /*<<< orphan*/  mp_aframe_set_chmap (struct mp_aframe*,struct mp_chmap*) ; 

__attribute__((used)) static bool reorder_planes(struct mp_aframe *mpa, int *reorder,
                           struct mp_chmap *newmap)
{
    if (!mp_aframe_set_chmap(mpa, newmap))
        return false;

    int num_planes = mp_aframe_get_planes(mpa);
    uint8_t **planes = mp_aframe_get_data_rw(mpa);
    uint8_t *old_planes[MP_NUM_CHANNELS];
    assert(num_planes <= MP_NUM_CHANNELS);
    for (int n = 0; n < num_planes; n++)
        old_planes[n] = planes[n];

    int next_na = 0;
    for (int n = 0; n < num_planes; n++)
        next_na += newmap->speaker[n] != MP_SPEAKER_ID_NA;

    for (int n = 0; n < num_planes; n++) {
        int src = reorder[n];
        assert(src >= -1 && src < num_planes);
        if (src >= 0) {
            planes[n] = old_planes[src];
        } else {
            assert(next_na < num_planes);
            planes[n] = old_planes[next_na++];
            // The NA planes were never written by avrctx, so clear them.
            af_fill_silence(planes[n],
                            mp_aframe_get_sstride(mpa) * mp_aframe_get_size(mpa),
                            mp_aframe_get_format(mpa));
        }
    }

    return true;
}