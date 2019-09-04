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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;
struct host_cmd_ds_802_11_snmp_mib {int /*<<< orphan*/  value; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  query_type; int /*<<< orphan*/  oid; } ;
struct TYPE_2__ {struct host_cmd_ds_802_11_snmp_mib smib; } ;
struct host_cmd_ds_command {TYPE_1__ params; } ;

/* Variables and functions */
#define  DTIM_PERIOD_I 131 
#define  FRAG_THRESH_I 130 
 scalar_t__ HostCmd_ACT_GEN_GET ; 
 int /*<<< orphan*/  INFO ; 
#define  RTS_THRESH_I 129 
#define  SHORT_RETRY_LIM_I 128 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 

__attribute__((used)) static int mwifiex_ret_802_11_snmp_mib(struct mwifiex_private *priv,
				       struct host_cmd_ds_command *resp,
				       u32 *data_buf)
{
	struct host_cmd_ds_802_11_snmp_mib *smib = &resp->params.smib;
	u16 oid = le16_to_cpu(smib->oid);
	u16 query_type = le16_to_cpu(smib->query_type);
	u32 ul_temp;

	mwifiex_dbg(priv->adapter, INFO,
		    "info: SNMP_RESP: oid value = %#x,\t"
		    "query_type = %#x, buf size = %#x\n",
		    oid, query_type, le16_to_cpu(smib->buf_size));
	if (query_type == HostCmd_ACT_GEN_GET) {
		ul_temp = get_unaligned_le16(smib->value);
		if (data_buf)
			*data_buf = ul_temp;
		switch (oid) {
		case FRAG_THRESH_I:
			mwifiex_dbg(priv->adapter, INFO,
				    "info: SNMP_RESP: FragThsd =%u\n",
				    ul_temp);
			break;
		case RTS_THRESH_I:
			mwifiex_dbg(priv->adapter, INFO,
				    "info: SNMP_RESP: RTSThsd =%u\n",
				    ul_temp);
			break;
		case SHORT_RETRY_LIM_I:
			mwifiex_dbg(priv->adapter, INFO,
				    "info: SNMP_RESP: TxRetryCount=%u\n",
				    ul_temp);
			break;
		case DTIM_PERIOD_I:
			mwifiex_dbg(priv->adapter, INFO,
				    "info: SNMP_RESP: DTIM period=%u\n",
				    ul_temp);
		default:
			break;
		}
	}

	return 0;
}