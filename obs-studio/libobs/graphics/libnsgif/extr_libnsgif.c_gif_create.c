#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gif_bitmap_callback_vt ;
struct TYPE_4__ {int /*<<< orphan*/  decoded_frame; int /*<<< orphan*/  bitmap_callbacks; } ;
typedef  TYPE_1__ gif_animation ;

/* Variables and functions */
 int /*<<< orphan*/  GIF_INVALID_FRAME ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void gif_create(gif_animation *gif, gif_bitmap_callback_vt *bitmap_callbacks) {
    memset(gif, 0, sizeof(gif_animation));
    gif->bitmap_callbacks = *bitmap_callbacks;
    gif->decoded_frame = GIF_INVALID_FRAME;
}