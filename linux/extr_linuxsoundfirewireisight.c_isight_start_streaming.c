#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  channel; } ;
struct TYPE_7__ {TYPE_2__* packets; int /*<<< orphan*/  iso_buffer; } ;
struct isight {scalar_t__ packet_index; int first_packet; TYPE_4__ resources; int /*<<< orphan*/ * context; TYPE_3__ buffer; TYPE_1__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_speed; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ENABLE ; 
 int /*<<< orphan*/  FW_ISO_CONTEXT_MATCH_ALL_TAGS ; 
 int /*<<< orphan*/  FW_ISO_CONTEXT_RECEIVE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 unsigned int QUEUE_LENGTH ; 
 int /*<<< orphan*/  RATE_48000 ; 
 int /*<<< orphan*/  REG_AUDIO_ENABLE ; 
 int /*<<< orphan*/  REG_SAMPLE_RATE ; 
 int /*<<< orphan*/  audio_packet ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fw_iso_context_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct isight*) ; 
 int /*<<< orphan*/  fw_iso_context_destroy (int /*<<< orphan*/ *) ; 
 int fw_iso_context_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fw_iso_context_start (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_iso_resources_free (TYPE_4__*) ; 
 int isight_connect (struct isight*) ; 
 int /*<<< orphan*/  isight_packet ; 
 int /*<<< orphan*/  isight_stop_streaming (struct isight*) ; 
 int reg_write (struct isight*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isight_start_streaming(struct isight *isight)
{
	unsigned int i;
	int err;

	if (isight->context) {
		if (isight->packet_index < 0)
			isight_stop_streaming(isight);
		else
			return 0;
	}

	err = reg_write(isight, REG_SAMPLE_RATE, cpu_to_be32(RATE_48000));
	if (err < 0)
		goto error;

	err = isight_connect(isight);
	if (err < 0)
		goto error;

	err = reg_write(isight, REG_AUDIO_ENABLE, cpu_to_be32(AUDIO_ENABLE));
	if (err < 0)
		goto err_resources;

	isight->context = fw_iso_context_create(isight->device->card,
						FW_ISO_CONTEXT_RECEIVE,
						isight->resources.channel,
						isight->device->max_speed,
						4, isight_packet, isight);
	if (IS_ERR(isight->context)) {
		err = PTR_ERR(isight->context);
		isight->context = NULL;
		goto err_resources;
	}

	for (i = 0; i < QUEUE_LENGTH; ++i) {
		err = fw_iso_context_queue(isight->context, &audio_packet,
					   &isight->buffer.iso_buffer,
					   isight->buffer.packets[i].offset);
		if (err < 0)
			goto err_context;
	}

	isight->first_packet = true;
	isight->packet_index = 0;

	err = fw_iso_context_start(isight->context, -1, 0,
				   FW_ISO_CONTEXT_MATCH_ALL_TAGS/*?*/);
	if (err < 0)
		goto err_context;

	return 0;

err_context:
	fw_iso_context_destroy(isight->context);
	isight->context = NULL;
err_resources:
	fw_iso_resources_free(&isight->resources);
	reg_write(isight, REG_AUDIO_ENABLE, 0);
error:
	return err;
}