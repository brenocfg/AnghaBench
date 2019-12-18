#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gif_result ;
struct TYPE_5__ {unsigned char* gif_data; int buffer_position; int buffer_size; unsigned char loop_count; TYPE_1__* frames; } ;
typedef  TYPE_2__ gif_animation ;
struct TYPE_4__ {unsigned char frame_delay; int transparency; unsigned char transparency_index; unsigned char disposal_method; } ;

/* Variables and functions */
 unsigned char GIF_BLOCK_TERMINATOR ; 
 unsigned char GIF_DISPOSAL_MASK ; 
#define  GIF_EXTENSION_APPLICATION 130 
#define  GIF_EXTENSION_COMMENT 129 
#define  GIF_EXTENSION_GRAPHIC_CONTROL 128 
 unsigned char GIF_EXTENSION_INTRODUCER ; 
 unsigned char GIF_FRAME_QUIRKS_RESTORE ; 
 unsigned char GIF_FRAME_RESTORE ; 
 int /*<<< orphan*/  GIF_INSUFFICIENT_FRAME_DATA ; 
 int /*<<< orphan*/  GIF_OK ; 
 unsigned char GIF_TRANSPARENCY_MASK ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static gif_result gif_initialise_frame_extensions(gif_animation *gif, const int frame) {
    unsigned char *gif_data, *gif_end;
    int gif_bytes;
    unsigned int block_size;

    /*    Get our buffer position etc.
    */
    gif_data = (unsigned char *)(gif->gif_data + gif->buffer_position);
    gif_end = (unsigned char *)(gif->gif_data + gif->buffer_size);
    
    /*    Initialise the extensions
    */
    while (gif_data[0] == GIF_EXTENSION_INTRODUCER) {
        ++gif_data;
        gif_bytes = (unsigned int)(gif_end - gif_data);

        /*    Switch on extension label
        */
        switch(gif_data[0]) {
            /* 6-byte Graphic Control Extension is:
             *
             *    +0    CHAR    Graphic Control Label
             *    +1    CHAR    Block Size
             *    +2    CHAR    __Packed Fields__
             *            3BITS    Reserved
             *            3BITS    Disposal Method
             *            1BIT    User Input Flag
             *            1BIT    Transparent Color Flag
             *    +3    SHORT    Delay Time
             *    +5    CHAR    Transparent Color Index
            */
            case GIF_EXTENSION_GRAPHIC_CONTROL:
                if (gif_bytes < 6) return GIF_INSUFFICIENT_FRAME_DATA;
                gif->frames[frame].frame_delay = gif_data[3] | (gif_data[4] << 8);
                if (gif_data[2] & GIF_TRANSPARENCY_MASK) {
                    gif->frames[frame].transparency = true;
                    gif->frames[frame].transparency_index = gif_data[5];
                }
                gif->frames[frame].disposal_method = ((gif_data[2] & GIF_DISPOSAL_MASK) >> 2);
                /*    I have encountered documentation and GIFs in the wild that use
                 *    0x04 to restore the previous frame, rather than the officially
                 *    documented 0x03.  I believe some (older?) software may even actually
                 *    export this way.  We handle this as a type of "quirks" mode.
                */
                if (gif->frames[frame].disposal_method == GIF_FRAME_QUIRKS_RESTORE)
                    gif->frames[frame].disposal_method = GIF_FRAME_RESTORE;
                gif_data += (2 + gif_data[1]);
                break;

            /* 14-byte+ Application Extension is:
             *
             *    +0    CHAR    Application Extension Label
             *    +1    CHAR    Block Size
             *    +2    8CHARS    Application Identifier
             *    +10    3CHARS    Appl. Authentication Code
             *    +13    1-256    Application Data (Data sub-blocks)
            */
            case GIF_EXTENSION_APPLICATION:
                if (gif_bytes < 17) return GIF_INSUFFICIENT_FRAME_DATA;
                if ((gif_data[1] == 0x0b) &&
                    (strncmp((const char *) gif_data + 2,
                        "NETSCAPE2.0", 11) == 0) &&
                    (gif_data[13] == 0x03) &&
                    (gif_data[14] == 0x01)) {
                        gif->loop_count = gif_data[15] | (gif_data[16] << 8);
                }
                gif_data += (2 + gif_data[1]);
                break;

            /*    Move the pointer to the first data sub-block
             *    Skip 1 byte for the extension label
            */
            case GIF_EXTENSION_COMMENT:
                ++gif_data;
                break;

            /*    Move the pointer to the first data sub-block
             *    Skip 2 bytes for the extension label and size fields
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