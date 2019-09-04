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
typedef  int /*<<< orphan*/  u16 ;
struct request_context {int dummy; } ;
struct hermes_response {int dummy; } ;
struct hermes {struct ezusb_priv* priv; } ;
struct ezusb_priv {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EZUSB_FRAME_CONTROL ; 
 int /*<<< orphan*/  EZUSB_RID_ACK ; 
 int /*<<< orphan*/  EZUSB_RID_DOCMD ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ezusb_access_ltv (struct ezusb_priv*,struct request_context*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct request_context* ezusb_alloc_ctx (struct ezusb_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ezusb_doicmd_wait(struct hermes *hw, u16 cmd, u16 parm0, u16 parm1,
			     u16 parm2, struct hermes_response *resp)
{
	struct ezusb_priv *upriv = hw->priv;
	struct request_context *ctx;

	__le16 data[4] = {
		cpu_to_le16(cmd),
		cpu_to_le16(parm0),
		cpu_to_le16(parm1),
		cpu_to_le16(parm2),
	};
	netdev_dbg(upriv->dev,
		   "0x%04X, parm0 0x%04X, parm1 0x%04X, parm2 0x%04X\n", cmd,
		   parm0, parm1, parm2);
	ctx = ezusb_alloc_ctx(upriv, EZUSB_RID_DOCMD, EZUSB_RID_ACK);
	if (!ctx)
		return -ENOMEM;

	return ezusb_access_ltv(upriv, ctx, sizeof(data), &data,
				EZUSB_FRAME_CONTROL, NULL, 0, NULL);
}