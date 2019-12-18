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
typedef  int uint64_t ;
struct fall {int n_rot; int y_stop; scalar_t__ x_pos; int /*<<< orphan*/  shape; } ;
struct blocks {size_t* last_digits; struct block_state* states; TYPE_1__* gif; } ;
struct block_state {size_t num_to_draw; int fall_index; size_t block_index; scalar_t__ x_shift; } ;
typedef  enum rotation { ____Placeholder_rotation } rotation ;
struct TYPE_2__ {unsigned char* frame; int w; int h; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BLACK ; 
 int /*<<< orphan*/  COLOR_WHITE ; 
 int ROT_0 ; 
 int ROT_180 ; 
 int ROT_90 ; 
 int ROT_MAX ; 
 int /*<<< orphan*/  SHAPE_SQUARE ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t* block_sizes ; 
 int /*<<< orphan*/  draw_shape (int /*<<< orphan*/ ,scalar_t__,int,int,int,int,unsigned char*) ; 
 int /*<<< orphan*/  draw_shape_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,unsigned char*) ; 
 struct fall** fall ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 

uint64_t blocks_draw(struct blocks *blocks, bool odd_second)
{
    unsigned char *frame = blocks->gif->frame;
    int digits_fallen = 0;
    int i;
    int w = blocks->gif->w;
    int h = blocks->gif->h;

    memset(frame, COLOR_BLACK, (size_t)(w * h));

    for (i = 0; i < 4; i++) {
        struct block_state *state = &blocks->states[i];

        if (state->num_to_draw != blocks->last_digits[i]) {
            state->fall_index = 0;
            state->block_index = 0;
            blocks->last_digits[i] = state->num_to_draw;
        }

        if (state->block_index < block_sizes[state->num_to_draw]) {
            const struct fall *curr =
                &fall[state->num_to_draw][state->block_index];
            int rotations = curr->n_rot;

            switch (rotations) {
            case 1:
                if (state->fall_index < curr->y_stop / 2)
                    rotations = ROT_0;
                break;
            case 2:
                if (state->fall_index < curr->y_stop / 3)
                    rotations = ROT_0;
                else if (state->fall_index < curr->y_stop / 3 * 2)
                    rotations = ROT_90;
                break;
            case 3:
                if (state->fall_index < curr->y_stop / 4)
                    rotations = ROT_0;
                else if (state->fall_index < curr->y_stop / 4 * 2)
                    rotations = ROT_90;
                else if (state->fall_index < curr->y_stop / 4 * 3)
                    rotations = ROT_180;
                break;
            }

            assert(rotations >= 0 && rotations < ROT_MAX);

            draw_shape(curr->shape, curr->x_pos + state->x_shift,
                       state->fall_index - 1, w, h,
                       (enum rotation)rotations, frame);
            state->fall_index++;

            if (state->fall_index > curr->y_stop) {
                state->fall_index = 0;
                state->block_index++;
            }

            digits_fallen++;
        }

        if (state->block_index > 0) {
            for (int j = 0; j < state->block_index; j++) {
                const struct fall *fallen = &fall[state->num_to_draw][j];

                draw_shape(fallen->shape, fallen->x_pos + state->x_shift,
                           fallen->y_stop - 1, w, h, fallen->n_rot, frame);
            }
        }
    }

    if (odd_second) {
        draw_shape_full(SHAPE_SQUARE, COLOR_WHITE, 15, 13, w, h, ROT_0, frame);
        draw_shape_full(SHAPE_SQUARE, COLOR_WHITE, 15, 9, w, h, ROT_0, frame);
    }

    return digits_fallen ? 100 : 500;
}