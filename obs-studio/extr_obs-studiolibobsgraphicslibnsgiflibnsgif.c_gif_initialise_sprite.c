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
struct bitmap {int dummy; } ;
typedef  int /*<<< orphan*/  gif_result ;
struct TYPE_4__ {struct bitmap* (* bitmap_destroy ) (struct bitmap*) ;struct bitmap* (* bitmap_create ) (unsigned int,unsigned int) ;} ;
struct TYPE_5__ {unsigned int width; unsigned int height; int /*<<< orphan*/  decoded_frame; struct bitmap* frame_image; TYPE_1__ bitmap_callbacks; } ;
typedef  TYPE_2__ gif_animation ;

/* Variables and functions */
 int /*<<< orphan*/  GIF_INSUFFICIENT_MEMORY ; 
 int /*<<< orphan*/  GIF_INVALID_FRAME ; 
 int /*<<< orphan*/  GIF_OK ; 
 int /*<<< orphan*/  assert (struct bitmap* (*) (unsigned int,unsigned int)) ; 
 struct bitmap* stub1 (unsigned int,unsigned int) ; 
 struct bitmap* stub2 (struct bitmap*) ; 

__attribute__((used)) static gif_result gif_initialise_sprite(gif_animation *gif, unsigned int width, unsigned int height) {
    unsigned int max_width;
    unsigned int max_height;
    struct bitmap *buffer;

    /*    Check if we've changed
    */
    if ((width <= gif->width) && (height <= gif->height))
        return GIF_OK;

    /*    Get our maximum values
    */
    max_width = (width > gif->width) ? width : gif->width;
    max_height = (height > gif->height) ? height : gif->height;

    /*    Allocate some more memory
    */
    assert(gif->bitmap_callbacks.bitmap_create);
    if ((buffer = gif->bitmap_callbacks.bitmap_create(max_width, max_height)) == NULL)
        return GIF_INSUFFICIENT_MEMORY;
    assert(gif->bitmap_callbacks.bitmap_destroy);
    gif->bitmap_callbacks.bitmap_destroy(gif->frame_image);
    gif->frame_image = buffer;
    gif->width = max_width;
    gif->height = max_height;

    /*    Invalidate our currently decoded image
    */
    gif->decoded_frame = GIF_INVALID_FRAME;
    return GIF_OK;
}