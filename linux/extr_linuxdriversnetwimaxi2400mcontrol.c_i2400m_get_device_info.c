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
struct sk_buff {scalar_t__ data; } ;
struct i2400m_tlv_hdr {int dummy; } ;
struct i2400m_tlv_detailed_device_info {int dummy; } ;
struct i2400m_l3l4_hdr {int /*<<< orphan*/  pl; void* version; scalar_t__ length; void* type; } ;
struct i2400m {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  strerr ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2400M_L3L4_VERSION ; 
 int /*<<< orphan*/  I2400M_MT_GET_DEVICE_INFO ; 
 int /*<<< orphan*/  I2400M_TLV_DETAILED_DEVICE_INFO ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  PTR_ERR (struct sk_buff*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int i2400m_msg_check_status (struct i2400m_l3l4_hdr const*,char*,int) ; 
 struct sk_buff* i2400m_msg_to_dev (struct i2400m*,struct i2400m_l3l4_hdr*,int) ; 
 struct i2400m_tlv_hdr* i2400m_tlv_find (struct i2400m*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct i2400m_l3l4_hdr*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct i2400m_l3l4_hdr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 struct i2400m_l3l4_hdr* wimax_msg_data_len (struct sk_buff*,size_t*) ; 

struct sk_buff *i2400m_get_device_info(struct i2400m *i2400m)
{
	int result;
	struct device *dev = i2400m_dev(i2400m);
	struct sk_buff *ack_skb;
	struct i2400m_l3l4_hdr *cmd;
	const struct i2400m_l3l4_hdr *ack;
	size_t ack_len;
	const struct i2400m_tlv_hdr *tlv;
	const struct i2400m_tlv_detailed_device_info *ddi;
	char strerr[32];

	ack_skb = ERR_PTR(-ENOMEM);
	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		goto error_alloc;
	cmd->type = cpu_to_le16(I2400M_MT_GET_DEVICE_INFO);
	cmd->length = 0;
	cmd->version = cpu_to_le16(I2400M_L3L4_VERSION);

	ack_skb = i2400m_msg_to_dev(i2400m, cmd, sizeof(*cmd));
	if (IS_ERR(ack_skb)) {
		dev_err(dev, "Failed to issue 'get device info' command: %ld\n",
			PTR_ERR(ack_skb));
		goto error_msg_to_dev;
	}
	ack = wimax_msg_data_len(ack_skb, &ack_len);
	result = i2400m_msg_check_status(ack, strerr, sizeof(strerr));
	if (result < 0) {
		dev_err(dev, "'get device info' (0x%04x) command failed: "
			"%d - %s\n", I2400M_MT_GET_DEVICE_INFO, result,
			strerr);
		goto error_cmd_failed;
	}
	tlv = i2400m_tlv_find(i2400m, ack->pl, ack_len - sizeof(*ack),
			      I2400M_TLV_DETAILED_DEVICE_INFO, sizeof(*ddi));
	if (tlv == NULL) {
		dev_err(dev, "GET DEVICE INFO: "
			"detailed device info TLV not found (0x%04x)\n",
			I2400M_TLV_DETAILED_DEVICE_INFO);
		result = -EIO;
		goto error_no_tlv;
	}
	skb_pull(ack_skb, (void *) tlv - (void *) ack_skb->data);
error_msg_to_dev:
	kfree(cmd);
error_alloc:
	return ack_skb;

error_no_tlv:
error_cmd_failed:
	kfree_skb(ack_skb);
	kfree(cmd);
	return ERR_PTR(result);
}