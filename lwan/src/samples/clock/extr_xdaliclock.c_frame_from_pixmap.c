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
struct frame {TYPE_1__* scanlines; } ;
struct TYPE_2__ {scalar_t__* right; scalar_t__* left; } ;
typedef  scalar_t__ POS ;

/* Variables and functions */
 int MAX_SEGS_PER_LINE ; 
 struct frame* frame_mk (int,int) ; 
 scalar_t__ get_bit (unsigned char const*,int,int,int) ; 
 int /*<<< orphan*/  lwan_status_critical (char*) ; 

__attribute__((used)) static struct frame *
frame_from_pixmap(const unsigned char *bits, int width, int height)
{
    int x, y;
    struct frame *frame;
    POS *left, *right;
    POS half_width = (POS)(width / 2);

    frame = frame_mk(width, height);
    if (!frame)
        return NULL;

    for (y = 0; y < height; y++) {
        int seg, end;
        x = 0;

        left = frame->scanlines[y].left;
        right = frame->scanlines[y].right;

        for (seg = 0; seg < MAX_SEGS_PER_LINE; seg++) {
            left[seg] = half_width;
            right[seg] = half_width;
        }

        for (seg = 0; seg < MAX_SEGS_PER_LINE; seg++) {
            for (; x < width; x++) {
                if (get_bit(bits, x, y, width))
                    break;
            }
            if (x == width)
                break;
            left[seg] = (POS)x;
            for (; x < width; x++) {
                if (!get_bit(bits, x, y, width))
                    break;
            }
            right[seg] = (POS)x;
        }

        for (; x < width; x++) {
            if (get_bit(bits, x, y, width)) {
                lwan_status_critical(
                    "Font too curvy. Increase MAX_SEGS_PER_LINE "
                    "and recompile");
                return NULL;
            }
        }

        /* If there were any segments on this line, then replicate the last
           one out to the end of the line.  If it's blank, leave it alone,
           meaning it will be a 0-pixel-wide line down the middle.
         */
        end = seg;
        if (end > 0) {
            for (; seg < MAX_SEGS_PER_LINE; seg++) {
                left[seg] = left[end - 1];
                right[seg] = right[end - 1];
            }
        }
    }

    return frame;
}