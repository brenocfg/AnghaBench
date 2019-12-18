#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* cue_tail; } ;
typedef  TYPE_2__ vtt_t ;
struct TYPE_14__ {scalar_t__ timestamp; } ;
typedef  TYPE_3__ vtt_block_t ;
typedef  int /*<<< orphan*/  utf8_char_t ;
struct TYPE_15__ {scalar_t__ timestamp; } ;
typedef  TYPE_4__ caption_frame_t ;
struct TYPE_12__ {scalar_t__ duration; scalar_t__ timestamp; } ;

/* Variables and functions */
 scalar_t__ CAPTION_FRAME_TEXT_BYTES ; 
 int /*<<< orphan*/  VTT_CUE ; 
 int /*<<< orphan*/  caption_frame_to_text (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/ * vtt_block_data (TYPE_3__*) ; 
 TYPE_3__* vtt_block_new (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

vtt_block_t* vtt_cue_from_caption_frame(caption_frame_t* frame, vtt_t* vtt)
{
    if (vtt->cue_tail && 0 >= vtt->cue_tail->duration) {
        vtt->cue_tail->duration = frame->timestamp - vtt->cue_tail->timestamp;
    }

    // CRLF per row, plus an extra at the end
    vtt_block_t* cue = vtt_block_new(vtt, NULL, 2 + CAPTION_FRAME_TEXT_BYTES, VTT_CUE);
    utf8_char_t* data = vtt_block_data(cue);

    caption_frame_to_text(frame, data);
    cue->timestamp = frame->timestamp;
    // vtt requires an extra new line
    strcat((char*)data, "\r\n");
    return cue;
}