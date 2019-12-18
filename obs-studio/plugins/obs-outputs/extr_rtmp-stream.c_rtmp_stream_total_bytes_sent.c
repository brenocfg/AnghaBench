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
typedef  int /*<<< orphan*/  uint64_t ;
struct rtmp_stream {int /*<<< orphan*/  total_bytes_sent; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t rtmp_stream_total_bytes_sent(void *data)
{
	struct rtmp_stream *stream = data;
	return stream->total_bytes_sent;
}