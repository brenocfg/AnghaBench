#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ua101_stream {unsigned int queue_length; TYPE_1__** urbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kill_stream_urbs(struct ua101_stream *stream)
{
	unsigned int i;

	for (i = 0; i < stream->queue_length; ++i)
		if (stream->urbs[i])
			usb_kill_urb(&stream->urbs[i]->urb);
}