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
 int /*<<< orphan*/  PHY_GetTxPowerIndex_8723B (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

u8 PHY_GetTxPowerIndex(
	struct adapter *padapter,
	u8 RFPath,
	u8 Rate,
	enum CHANNEL_WIDTH BandWidth,
	u8 Channel
)
{
	return PHY_GetTxPowerIndex_8723B(padapter, RFPath, Rate, BandWidth, Channel);
}