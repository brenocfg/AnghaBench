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
struct qcom_glink {int dummy; } ;
struct glink_core_rx_intent {int size; int id; } ;
struct glink_channel {int /*<<< orphan*/  lcid; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  void* __le32 ;
typedef  void* __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  RPM_CMD_INTENT ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  qcom_glink_tx (struct qcom_glink*,struct command*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qcom_glink_advertise_intent(struct qcom_glink *glink,
				       struct glink_channel *channel,
				       struct glink_core_rx_intent *intent)
{
	struct command {
		__le16 id;
		__le16 lcid;
		__le32 count;
		__le32 size;
		__le32 liid;
	} __packed;
	struct command cmd;

	cmd.id = cpu_to_le16(RPM_CMD_INTENT);
	cmd.lcid = cpu_to_le16(channel->lcid);
	cmd.count = cpu_to_le32(1);
	cmd.size = cpu_to_le32(intent->size);
	cmd.liid = cpu_to_le32(intent->id);

	qcom_glink_tx(glink, &cmd, sizeof(cmd), NULL, 0, true);

	return 0;
}