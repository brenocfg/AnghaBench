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
struct video_input {int /*<<< orphan*/  scaler; int /*<<< orphan*/ * frame; } ;

/* Variables and functions */
 size_t MAX_CONVERT_BUFFERS ; 
 int /*<<< orphan*/  video_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_scaler_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void video_input_free(struct video_input *input)
{
	for (size_t i = 0; i < MAX_CONVERT_BUFFERS; i++)
		video_frame_free(&input->frame[i]);
	video_scaler_destroy(input->scaler);
}