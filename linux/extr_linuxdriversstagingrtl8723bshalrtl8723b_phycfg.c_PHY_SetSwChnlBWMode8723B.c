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
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;
typedef  enum CHANNEL_WIDTH { ____Placeholder_CHANNEL_WIDTH } CHANNEL_WIDTH ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_HandleSwChnlAndSetBW8723B (struct adapter*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void PHY_SetSwChnlBWMode8723B(
	struct adapter *Adapter,
	u8 channel,
	enum CHANNEL_WIDTH Bandwidth,
	u8 Offset40,
	u8 Offset80
)
{
	/* DBG_871X("%s() ===>\n", __func__); */

	PHY_HandleSwChnlAndSetBW8723B(Adapter, true, true, channel, Bandwidth, Offset40, Offset80, channel);

	/* DBG_871X("<==%s()\n", __func__); */
}