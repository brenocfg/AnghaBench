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
struct pcxhr_stream {scalar_t__ status; struct pcxhr_pipe* pipe; } ;
struct pcxhr_pipe {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCXHR_STREAM_STATUS_SCHEDULE_RUN ; 

__attribute__((used)) static inline int pcxhr_stream_scheduled_get_pipe(struct pcxhr_stream *stream,
						  struct pcxhr_pipe **pipe)
{
	if (stream->status == PCXHR_STREAM_STATUS_SCHEDULE_RUN) {
		*pipe = stream->pipe;
		return 1;
	}
	return 0;
}