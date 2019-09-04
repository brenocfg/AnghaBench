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
struct gbaudio_module_info {int /*<<< orphan*/  dev; } ;
struct gb_audio_streaming_event_request {int /*<<< orphan*/  event; int /*<<< orphan*/  data_cport; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gbaudio_request_stream(struct gbaudio_module_info *module,
				  struct gb_audio_streaming_event_request *req)
{
	dev_warn(module->dev, "Audio Event received: cport: %u, event: %u\n",
		 le16_to_cpu(req->data_cport), req->event);

	return 0;
}