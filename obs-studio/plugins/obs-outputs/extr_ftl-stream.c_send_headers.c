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
struct ftl_stream {int sent_headers; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  send_video_header (struct ftl_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool send_headers(struct ftl_stream *stream, int64_t dts_usec)
{
	stream->sent_headers = true;

	if (!send_video_header(stream, dts_usec))
		return false;

	return true;
}