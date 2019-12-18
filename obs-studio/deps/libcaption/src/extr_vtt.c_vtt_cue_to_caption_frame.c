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
typedef  int /*<<< orphan*/  vtt_block_t ;
typedef  int /*<<< orphan*/  caption_frame_t ;

/* Variables and functions */
 int caption_frame_from_text (int /*<<< orphan*/ *,char const*) ; 
 char* vtt_block_data (int /*<<< orphan*/ *) ; 

int vtt_cue_to_caption_frame(vtt_block_t* cue, caption_frame_t* frame)
{
    const char* data = vtt_block_data(cue);
    return caption_frame_from_text(frame, data);
}