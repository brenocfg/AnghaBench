#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int curbit; int code_size; int lastbit; int get_done; unsigned char* buf; unsigned char* direct; int last_byte; unsigned char* gif_data; int buffer_position; int zero_data_block; scalar_t__ buffer_size; } ;
typedef  TYPE_1__ gif_animation ;

/* Variables and functions */
 int GIF_END_OF_FRAME ; 
 int GIF_INSUFFICIENT_FRAME_DATA ; 
 int* maskTbl ; 

__attribute__((used)) static int gif_next_code(gif_animation *gif, int code_size) {
    int i, j, end, count, ret;
    unsigned char *b;

    (void)code_size;

    end = gif->curbit + gif->code_size;
    if (end >= gif->lastbit) {
        if (gif->get_done)
            return GIF_END_OF_FRAME;
        gif->buf[0] = gif->direct[gif->last_byte - 2];
        gif->buf[1] = gif->direct[gif->last_byte - 1];

        /* get the next block */
        gif->direct = gif->gif_data + gif->buffer_position;
        gif->zero_data_block = ((count = gif->direct[0]) == 0);
        if ((gif->buffer_position + count) >= gif->buffer_size)
            return GIF_INSUFFICIENT_FRAME_DATA;
        if (count == 0)
            gif->get_done = true;
        else {
            gif->direct -= 1;
            gif->buf[2] = gif->direct[2];
            gif->buf[3] = gif->direct[3];
        }
        gif->buffer_position += count + 1;

        /* update our variables */
        gif->last_byte = 2 + count;
        gif->curbit = (gif->curbit - gif->lastbit) + 16;
        gif->lastbit = (2 + count) << 3;
        end = gif->curbit + gif->code_size;
    }

    i = gif->curbit >> 3;
    if (i < 2)
        b = gif->buf;
    else
        b = gif->direct;

    ret = b[i];
    j = (end >> 3) - 1;
    if (i <= j) {
        ret |= (b[i + 1] << 8);
        if (i < j)
            ret |= (b[i + 2] << 16);
    }
    ret = (ret >> (gif->curbit % 8)) & maskTbl[gif->code_size];
    gif->curbit += gif->code_size;
    return ret;
}