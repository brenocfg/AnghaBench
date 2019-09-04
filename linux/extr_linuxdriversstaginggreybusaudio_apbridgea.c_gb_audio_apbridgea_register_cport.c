#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gb_connection {int /*<<< orphan*/  hd; int /*<<< orphan*/  bundle; } ;
struct TYPE_2__ {void* i2s_port; int /*<<< orphan*/  type; } ;
struct audio_apbridgea_register_cport_request {int /*<<< orphan*/  direction; void* cport; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_APBRIDGEA_TYPE_REGISTER_CPORT ; 
 int /*<<< orphan*/  GB_APB_REQUEST_AUDIO_CONTROL ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int gb_hd_output (int /*<<< orphan*/ ,struct audio_apbridgea_register_cport_request*,int,int /*<<< orphan*/ ,int) ; 
 int gb_pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

int gb_audio_apbridgea_register_cport(struct gb_connection *connection,
				      __u16 i2s_port, __u16 cportid,
				      __u8 direction)
{
	struct audio_apbridgea_register_cport_request req;
	int ret;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_REGISTER_CPORT;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);
	req.cport = cpu_to_le16(cportid);
	req.direction = direction;

	ret = gb_pm_runtime_get_sync(connection->bundle);
	if (ret)
		return ret;

	return gb_hd_output(connection->hd, &req, sizeof(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
}