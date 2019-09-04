#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uas_stream {TYPE_1__* req_status; TYPE_3__* req_out; TYPE_2__* req_in; } ;
struct f_uas {struct uas_stream* stream; } ;
struct TYPE_6__ {int stream_id; } ;
struct TYPE_5__ {int stream_id; } ;
struct TYPE_4__ {int stream_id; } ;

/* Variables and functions */

__attribute__((used)) static void uasp_setup_stream_res(struct f_uas *fu, int max_streams)
{
	int i;

	for (i = 0; i < max_streams; i++) {
		struct uas_stream *s = &fu->stream[i];

		s->req_in->stream_id = i + 1;
		s->req_out->stream_id = i + 1;
		s->req_status->stream_id = i + 1;
	}
}