#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gif_result ;
struct TYPE_7__ {int frame_pointer; int display; int virgin; scalar_t__ disposal_method; int transparency; int frame_delay; int redraw_required; unsigned int redraw_x; unsigned int redraw_width; unsigned int redraw_y; unsigned int redraw_height; } ;
typedef  TYPE_1__ gif_frame ;
struct TYPE_8__ {int frame_count; unsigned char* gif_data; int buffer_position; int buffer_size; int frame_holders; int decoded_frame; int frame_count_partial; TYPE_1__* frames; } ;
typedef  TYPE_2__ gif_animation ;

/* Variables and functions */
 unsigned int GIF_COLOUR_TABLE_MASK ; 
 unsigned int GIF_COLOUR_TABLE_SIZE_MASK ; 
 int /*<<< orphan*/  GIF_DATA_ERROR ; 
 scalar_t__ GIF_FRAME_CLEAR ; 
 int /*<<< orphan*/  GIF_FRAME_DATA_ERROR ; 
 scalar_t__ GIF_FRAME_RESTORE ; 
 unsigned char GIF_IMAGE_SEPARATOR ; 
 int /*<<< orphan*/  GIF_INSUFFICIENT_DATA ; 
 int /*<<< orphan*/  GIF_INSUFFICIENT_FRAME_DATA ; 
 int /*<<< orphan*/  GIF_INSUFFICIENT_MEMORY ; 
 int GIF_INVALID_FRAME ; 
 unsigned char GIF_MAX_LZW ; 
 int /*<<< orphan*/  GIF_OK ; 
 unsigned char GIF_TRAILER ; 
 int /*<<< orphan*/  GIF_WORKING ; 
 int /*<<< orphan*/  gif_initialise_frame_extensions (TYPE_2__*,int) ; 
 scalar_t__ gif_initialise_sprite (TYPE_2__*,unsigned int,unsigned int) ; 
 scalar_t__ realloc (TYPE_1__*,int) ; 

__attribute__((used)) static gif_result gif_initialise_frame(gif_animation *gif) {
    int frame;
    gif_frame *temp_buf;

    unsigned char *gif_data, *gif_end;
    int gif_bytes;
    unsigned int flags = 0;
    unsigned int width, height, offset_x, offset_y;
    unsigned int block_size, colour_table_size;
    bool first_image = true;
    gif_result return_value;

    /*    Get the frame to decode and our data position
    */
    frame = gif->frame_count;

    /*    Get our buffer position etc.
    */
    gif_data = (unsigned char *)(gif->gif_data + gif->buffer_position);
    gif_end = (unsigned char *)(gif->gif_data + gif->buffer_size);
    gif_bytes = (unsigned int)(gif_end - gif_data);

    /*    Check if we've finished
    */
    if ((gif_bytes > 0) && (gif_data[0] == GIF_TRAILER)) return GIF_OK;
    
    /*    Check if we have enough data
     *    The shortest block of data is a 4-byte comment extension + 1-byte block terminator + 1-byte gif trailer
    */
    if (gif_bytes < 6) return GIF_INSUFFICIENT_DATA;

    /*    We could theoretically get some junk data that gives us millions of frames, so
        we ensure that we don't have a silly number
    */
    if (frame > 4096) return GIF_FRAME_DATA_ERROR;

    /*    Get some memory to store our pointers in etc.
    */
    if ((int)gif->frame_holders <= frame) {
        /*    Allocate more memory
        */
        if ((temp_buf = (gif_frame *)realloc(gif->frames,
                    (frame + 1) * sizeof(gif_frame))) == NULL)
            return GIF_INSUFFICIENT_MEMORY;
        gif->frames = temp_buf;
        gif->frame_holders = frame + 1;
    }

    /*    Store our frame pointer. We would do it when allocating except we
        start off with one frame allocated so we can always use realloc.
    */
    gif->frames[frame].frame_pointer = gif->buffer_position;
    gif->frames[frame].display = false;
    gif->frames[frame].virgin = true;
    gif->frames[frame].disposal_method = 0;
    gif->frames[frame].transparency = false;
    gif->frames[frame].frame_delay = 100;
    gif->frames[frame].redraw_required = false;

    /*    Invalidate any previous decoding we have of this frame
    */
    if (gif->decoded_frame == frame)
        gif->decoded_frame = GIF_INVALID_FRAME;

    /*    We pretend to initialise the frames, but really we just skip over all
        the data contained within. This is all basically a cut down version of
        gif_decode_frame that doesn't have any of the LZW bits in it.
    */

    /*    Initialise any extensions
    */
    gif->buffer_position = (unsigned int)(gif_data - gif->gif_data);
    if ((return_value = gif_initialise_frame_extensions(gif, frame)) != GIF_OK)
        return return_value;
    gif_data = (gif->gif_data + gif->buffer_position);
    gif_bytes = (unsigned int)(gif_end - gif_data);

    /*    Check if we've finished
    */
    if ((gif_bytes = (unsigned int)(gif_end - gif_data)) < 1)
        return GIF_INSUFFICIENT_FRAME_DATA;
    else if (gif_data[0] == GIF_TRAILER) {
        gif->buffer_position = (unsigned int)(gif_data - gif->gif_data);
        gif->frame_count = frame + 1;
        return GIF_OK;
    }

    /*    If we're not done, there should be an image descriptor
    */
    if (gif_data[0] != GIF_IMAGE_SEPARATOR) return GIF_FRAME_DATA_ERROR;

    /*    Do some simple boundary checking
    */
    offset_x = gif_data[1] | (gif_data[2] << 8);
    offset_y = gif_data[3] | (gif_data[4] << 8);
    width = gif_data[5] | (gif_data[6] << 8);
    height = gif_data[7] | (gif_data[8] << 8);

    /*    Set up the redraw characteristics. We have to check for extending the area
        due to multi-image frames.
    */
    if (!first_image) {
        if (gif->frames[frame].redraw_x > offset_x) {
            gif->frames[frame].redraw_width += (gif->frames[frame].redraw_x - offset_x);
            gif->frames[frame].redraw_x = offset_x;
        }
        if (gif->frames[frame].redraw_y > offset_y) {
            gif->frames[frame].redraw_height += (gif->frames[frame].redraw_y - offset_y);
            gif->frames[frame].redraw_y = offset_y;
        }
        if ((offset_x + width) > (gif->frames[frame].redraw_x + gif->frames[frame].redraw_width))
            gif->frames[frame].redraw_width = (offset_x + width) - gif->frames[frame].redraw_x;
        if ((offset_y + height) > (gif->frames[frame].redraw_y + gif->frames[frame].redraw_height))
            gif->frames[frame].redraw_height = (offset_y + height) - gif->frames[frame].redraw_y;
    } else {
        first_image = false;
        gif->frames[frame].redraw_x = offset_x;
        gif->frames[frame].redraw_y = offset_y;
        gif->frames[frame].redraw_width = width;
        gif->frames[frame].redraw_height = height;
    }

    /*    if we are clearing the background then we need to redraw enough to cover the previous
        frame too
    */
    gif->frames[frame].redraw_required = ((gif->frames[frame].disposal_method == GIF_FRAME_CLEAR) ||
                        (gif->frames[frame].disposal_method == GIF_FRAME_RESTORE));

    /*    Boundary checking - shouldn't ever happen except with junk data
    */
    if (gif_initialise_sprite(gif, (offset_x + width), (offset_y + height)))
        return GIF_INSUFFICIENT_MEMORY;

    /*    Decode the flags
    */
    flags = gif_data[9];
    colour_table_size = 2 << (flags & GIF_COLOUR_TABLE_SIZE_MASK);

    /*    Move our data onwards and remember we've got a bit of this frame
    */
    gif_data += 10;
    gif_bytes = (unsigned int)(gif_end - gif_data);
    gif->frame_count_partial = frame + 1;

    /*    Skip the local colour table
    */
    if (flags & GIF_COLOUR_TABLE_MASK) {
        gif_data += 3 * colour_table_size;
        if ((gif_bytes = (unsigned int)(gif_end - gif_data)) < 0)
            return GIF_INSUFFICIENT_FRAME_DATA;
    }

    /*    Ensure we have a correct code size
    */
    if (gif_data[0] > GIF_MAX_LZW)
        return GIF_DATA_ERROR;

    /*    Move our pointer to the actual image data
    */
    gif_data++;
    if (--gif_bytes < 0)
        return GIF_INSUFFICIENT_FRAME_DATA;

    /*    Repeatedly skip blocks until we get a zero block or run out of data
     *    These blocks of image data are processed later by gif_decode_frame()
    */
    block_size = 0;
    while (block_size != 1) {
        block_size = gif_data[0] + 1;
        /*    Check if the frame data runs off the end of the file
        */
        if ((int)(gif_bytes - block_size) < 0) {
            /*    Try to recover by signaling the end of the gif.
             *    Once we get garbage data, there is no logical
             *    way to determine where the next frame is.
             *    It's probably better to partially load the gif
             *    than not at all.
            */
            if (gif_bytes >= 2) {
                gif_data[0] = 0;
                gif_data[1] = GIF_TRAILER;
                gif_bytes = 1;
                ++gif_data;
                break;
            } else
                return GIF_INSUFFICIENT_FRAME_DATA;
        } else {
            gif_bytes -= block_size;
            gif_data += block_size;
        }
    }

    /*    Add the frame and set the display flag
    */
    gif->buffer_position = (unsigned int)(gif_data - gif->gif_data);
    gif->frame_count = frame + 1;
    gif->frames[frame].display = true;

    /*    Check if we've finished
    */
    if (gif_bytes < 1)
        return GIF_INSUFFICIENT_FRAME_DATA;
    else
        if (gif_data[0] == GIF_TRAILER) return GIF_OK;
    return GIF_WORKING;
}