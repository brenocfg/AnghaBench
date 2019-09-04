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
struct gbaudio_module_info {int dummy; } ;
struct gb_operation_msg_hdr {int type; } ;
struct gb_operation {TYPE_1__* request; struct gb_connection* connection; } ;
struct gb_connection {TYPE_2__* bundle; } ;
struct gb_audio_streaming_event_request {int dummy; } ;
typedef  struct gb_audio_streaming_event_request gb_audio_jack_event_request ;
typedef  struct gb_audio_streaming_event_request gb_audio_button_event_request ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct gb_audio_streaming_event_request* payload; struct gb_operation_msg_hdr* header; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GB_AUDIO_TYPE_BUTTON_EVENT 130 
#define  GB_AUDIO_TYPE_JACK_EVENT 129 
#define  GB_AUDIO_TYPE_STREAMING_EVENT 128 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*) ; 
 int gbaudio_request_button (struct gbaudio_module_info*,struct gb_audio_streaming_event_request*) ; 
 int gbaudio_request_jack (struct gbaudio_module_info*,struct gb_audio_streaming_event_request*) ; 
 int gbaudio_request_stream (struct gbaudio_module_info*,struct gb_audio_streaming_event_request*) ; 
 struct gbaudio_module_info* greybus_get_drvdata (TYPE_2__*) ; 

__attribute__((used)) static int gbaudio_codec_request_handler(struct gb_operation *op)
{
	struct gb_connection *connection = op->connection;
	struct gbaudio_module_info *module =
		greybus_get_drvdata(connection->bundle);
	struct gb_operation_msg_hdr *header = op->request->header;
	struct gb_audio_streaming_event_request *stream_req;
	struct gb_audio_jack_event_request *jack_req;
	struct gb_audio_button_event_request *button_req;
	int ret;

	switch (header->type) {
	case GB_AUDIO_TYPE_STREAMING_EVENT:
		stream_req = op->request->payload;
		ret = gbaudio_request_stream(module, stream_req);
		break;

	case GB_AUDIO_TYPE_JACK_EVENT:
		jack_req = op->request->payload;
		ret = gbaudio_request_jack(module, jack_req);
		break;

	case GB_AUDIO_TYPE_BUTTON_EVENT:
		button_req = op->request->payload;
		ret = gbaudio_request_button(module, button_req);
		break;

	default:
		dev_err_ratelimited(&connection->bundle->dev,
				    "Invalid Audio Event received\n");
		return -EINVAL;
	}

	return ret;
}