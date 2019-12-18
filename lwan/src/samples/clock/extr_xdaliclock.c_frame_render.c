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
struct xdaliclock {TYPE_1__* gif_enc; } ;
struct scanline {int* left; int* right; } ;
struct frame {struct scanline* scanlines; } ;
struct TYPE_2__ {int /*<<< orphan*/  w; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKGROUND ; 
 int /*<<< orphan*/  FOREGROUND ; 
 int MAX_SEGS_PER_LINE ; 
 int char_height ; 
 int char_width ; 
 int /*<<< orphan*/  draw_horizontal_line (struct xdaliclock*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
frame_render(struct xdaliclock *xdc, const struct frame *frame, int x)
{
    for (int py = 0; py < char_height; py++) {
        const struct scanline *line = &frame->scanlines[py];
        int last_right = 0;
        int px = 0;

        goto first_iter;

        for (; px < MAX_SEGS_PER_LINE; px++) {
            if ((line->left[px] == line->right[px] ||
                 (line->left[px] == line->left[px - 1] &&
                  line->right[px] == line->right[px - 1]))) {
                continue;
            }

        first_iter:
            /* Erase the line between the last segment and this segment.
             */
            draw_horizontal_line(xdc, x + last_right, x + line->left[px], py,
                                 xdc->gif_enc->w, BACKGROUND);

            /* Draw the line of this segment.
             */
            draw_horizontal_line(xdc, x + line->left[px], x + line->right[px],
                                 py, xdc->gif_enc->w, FOREGROUND);

            last_right = line->right[px];
        }

        /* Erase the line between the last segment and the right edge.
         */
        draw_horizontal_line(xdc, x + last_right, x + char_width, py,
                             xdc->gif_enc->w, BACKGROUND);
    }
}