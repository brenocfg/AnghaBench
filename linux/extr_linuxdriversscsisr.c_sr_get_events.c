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
typedef  int u8 ;
struct scsi_sense_hdr {scalar_t__ sense_key; } ;
struct scsi_device {int dummy; } ;
struct media_event_desc {int media_event_code; } ;
struct event_header {int notification_class; scalar_t__ nea; int /*<<< orphan*/  data_len; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 unsigned int DISK_EVENT_EJECT_REQUEST ; 
 unsigned int DISK_EVENT_MEDIA_CHANGE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int GET_EVENT_STATUS_NOTIFICATION ; 
 int /*<<< orphan*/  MAX_RETRIES ; 
 int /*<<< orphan*/  SR_TIMEOUT ; 
 scalar_t__ UNIT_ATTENTION ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int scsi_execute_req (struct scsi_device*,int*,int /*<<< orphan*/ ,int*,int,struct scsi_sense_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_sense_valid (struct scsi_sense_hdr*) ; 

__attribute__((used)) static unsigned int sr_get_events(struct scsi_device *sdev)
{
	u8 buf[8];
	u8 cmd[] = { GET_EVENT_STATUS_NOTIFICATION,
		     1,			/* polled */
		     0, 0,		/* reserved */
		     1 << 4,		/* notification class: media */
		     0, 0,		/* reserved */
		     0, sizeof(buf),	/* allocation length */
		     0,			/* control */
	};
	struct event_header *eh = (void *)buf;
	struct media_event_desc *med = (void *)(buf + 4);
	struct scsi_sense_hdr sshdr;
	int result;

	result = scsi_execute_req(sdev, cmd, DMA_FROM_DEVICE, buf, sizeof(buf),
				  &sshdr, SR_TIMEOUT, MAX_RETRIES, NULL);
	if (scsi_sense_valid(&sshdr) && sshdr.sense_key == UNIT_ATTENTION)
		return DISK_EVENT_MEDIA_CHANGE;

	if (result || be16_to_cpu(eh->data_len) < sizeof(*med))
		return 0;

	if (eh->nea || eh->notification_class != 0x4)
		return 0;

	if (med->media_event_code == 1)
		return DISK_EVENT_EJECT_REQUEST;
	else if (med->media_event_code == 2)
		return DISK_EVENT_MEDIA_CHANGE;
	return 0;
}