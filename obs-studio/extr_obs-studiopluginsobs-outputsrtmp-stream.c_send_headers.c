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
struct rtmp_stream {int sent_headers; } ;

/* Variables and functions */
 int /*<<< orphan*/  send_audio_header (struct rtmp_stream*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  send_video_header (struct rtmp_stream*) ; 

__attribute__((used)) static inline bool send_headers(struct rtmp_stream *stream)
{
	stream->sent_headers = true;
	size_t i = 0;
	bool next = true;

	if (!send_audio_header(stream, i++, &next))
		return false;
	if (!send_video_header(stream))
		return false;

	while (next) {
		if (!send_audio_header(stream, i++, &next))
			return false;
	}

	return true;
}