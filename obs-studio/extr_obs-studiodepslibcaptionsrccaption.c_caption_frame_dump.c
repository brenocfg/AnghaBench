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
typedef  char utf8_char_t ;
typedef  int /*<<< orphan*/  caption_frame_t ;

/* Variables and functions */
 int CAPTION_FRAME_DUMP_BUF_SIZE ; 
 int /*<<< orphan*/  caption_frame_dump_buffer (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void caption_frame_dump(caption_frame_t* frame)
{
    utf8_char_t buff[CAPTION_FRAME_DUMP_BUF_SIZE];
    caption_frame_dump_buffer(frame, buff);
    fprintf(stderr, "%s\n", buff);
}