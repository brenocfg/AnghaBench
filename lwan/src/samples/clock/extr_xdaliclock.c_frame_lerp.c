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
struct xdaliclock {int* current_digits; int* target_digits; struct frame const* temp_frame; struct frame* clear_frame; } ;
struct scanline {void** right; void** left; } ;
struct frame {struct scanline* scanlines; } ;

/* Variables and functions */
 int MAX_SEGS_PER_LINE ; 
 struct frame** base_frames ; 
 int char_height ; 
 void* lerp (void*,void*,unsigned int) ; 

__attribute__((used)) static const struct frame *frame_lerp(struct xdaliclock *xdc, int digit, unsigned int anim)
{
    const int from = xdc->current_digits[digit];
    const int to = xdc->target_digits[digit];
    const struct frame *tof = (to >= 0) ? base_frames[to] : xdc->clear_frame;
    const struct frame *fromf;
    int x, y;

    if (from == to)
        return tof;

    fromf = (from >= 0) ? base_frames[from] : xdc->clear_frame;
    for (y = 0; y < char_height; y++) {
        struct scanline *line = &xdc->temp_frame->scanlines[y];
        const struct scanline *to_line = &tof->scanlines[y];
        const struct scanline *from_line = &fromf->scanlines[y];

        for (x = 0; x < MAX_SEGS_PER_LINE; x++) {
            line->left[x] = lerp(from_line->left[x], to_line->left[x], anim);
            line->right[x] = lerp(from_line->right[x], to_line->right[x], anim);
        }
    }

    return xdc->temp_frame;
}