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
struct iss_resizer_device {int /*<<< orphan*/  video_out; } ;
struct iss_buffer {int /*<<< orphan*/  iss_addr; } ;

/* Variables and functions */
 struct iss_buffer* omap4iss_video_buffer_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resizer_enable (struct iss_resizer_device*,int) ; 
 int /*<<< orphan*/  resizer_set_outaddr (struct iss_resizer_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resizer_isr_buffer(struct iss_resizer_device *resizer)
{
	struct iss_buffer *buffer;

	/* The whole resizer needs to be stopped. Disabling RZA only produces
	 * input FIFO overflows, most probably when the next frame is received.
	 */
	resizer_enable(resizer, 0);

	buffer = omap4iss_video_buffer_next(&resizer->video_out);
	if (!buffer)
		return;

	resizer_set_outaddr(resizer, buffer->iss_addr);

	resizer_enable(resizer, 1);
}