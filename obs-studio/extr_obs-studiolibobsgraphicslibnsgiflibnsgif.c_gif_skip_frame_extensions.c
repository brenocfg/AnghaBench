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
typedef  int /*<<< orphan*/  gif_result ;
struct TYPE_3__ {unsigned char* gif_data; int buffer_position; int buffer_size; } ;
typedef  TYPE_1__ gif_animation ;

/* Variables and functions */
 unsigned char GIF_BLOCK_TERMINATOR ; 
#define  GIF_EXTENSION_COMMENT 128 
 unsigned char GIF_EXTENSION_INTRODUCER ; 
 int /*<<< orphan*/  GIF_INSUFFICIENT_FRAME_DATA ; 
 int /*<<< orphan*/  GIF_OK ; 

__attribute__((used)) static gif_result gif_skip_frame_extensions(gif_animation *gif) {
    unsigned char *gif_data, *gif_end;
    int gif_bytes;
    unsigned int block_size;

    /*    Get our buffer position etc.
    */
    gif_data = (unsigned char *)(gif->gif_data + gif->buffer_position);
    gif_end = (unsigned char *)(gif->gif_data + gif->buffer_size);
    gif_bytes = (unsigned int)(gif_end - gif_data);

    /*    Skip the extensions
    */
    while (gif_data[0] == GIF_EXTENSION_INTRODUCER) {
        ++gif_data;

        /*    Switch on extension label
        */
        switch(gif_data[0]) {
            /*    Move the pointer to the first data sub-block
             *    1 byte for the extension label
            */
            case GIF_EXTENSION_COMMENT:
                ++gif_data;
                break;

            /*    Move the pointer to the first data sub-block
             *    2 bytes for the extension label and size fields
             *    Skip the extension size itself
            */
            default:
                gif_data += (2 + gif_data[1]);
        }

        /*    Repeatedly skip blocks until we get a zero block or run out of data
         *    This data is ignored by this gif decoder
        */
        gif_bytes = (unsigned int)(gif_end - gif_data);
        block_size = 0;
        while (gif_data[0] != GIF_BLOCK_TERMINATOR) {
            block_size = gif_data[0] + 1;
            if ((gif_bytes -= block_size) < 0)
                return GIF_INSUFFICIENT_FRAME_DATA;
            gif_data += block_size;
        }
        ++gif_data;
    }

    /*    Set buffer position and return
    */
    gif->buffer_position = (unsigned int)(gif_data - gif->gif_data);
    return GIF_OK;
}