#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int (* encode ) (int /*<<< orphan*/ ,struct encoder_frame*,struct encoder_packet*,int*) ;} ;
struct obs_encoder {scalar_t__ profile_encoder_encode_name; TYPE_2__ context; TYPE_1__ info; int /*<<< orphan*/  timebase_den; int /*<<< orphan*/  timebase_num; } ;
struct encoder_packet {struct obs_encoder* encoder; int /*<<< orphan*/  timebase_den; int /*<<< orphan*/  timebase_num; int /*<<< orphan*/  member_0; } ;
struct encoder_frame {int dummy; } ;

/* Variables and functions */
 scalar_t__ do_encode_name ; 
 int /*<<< orphan*/  obs_get_profiler_name_store () ; 
 int /*<<< orphan*/  profile_end (scalar_t__) ; 
 int /*<<< orphan*/  profile_start (scalar_t__) ; 
 scalar_t__ profile_store_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_off_encoder_packet (struct obs_encoder*,int,int,struct encoder_packet*) ; 
 int stub1 (int /*<<< orphan*/ ,struct encoder_frame*,struct encoder_packet*,int*) ; 

void do_encode(struct obs_encoder *encoder, struct encoder_frame *frame)
{
	profile_start(do_encode_name);
	if (!encoder->profile_encoder_encode_name)
		encoder->profile_encoder_encode_name =
			profile_store_name(obs_get_profiler_name_store(),
					"encode(%s)", encoder->context.name);

	struct encoder_packet pkt = {0};
	bool received = false;
	bool success;

	pkt.timebase_num = encoder->timebase_num;
	pkt.timebase_den = encoder->timebase_den;
	pkt.encoder = encoder;

	profile_start(encoder->profile_encoder_encode_name);
	success = encoder->info.encode(encoder->context.data, frame, &pkt,
			&received);
	profile_end(encoder->profile_encoder_encode_name);
	send_off_encoder_packet(encoder, success, received, &pkt);

	profile_end(do_encode_name);
}