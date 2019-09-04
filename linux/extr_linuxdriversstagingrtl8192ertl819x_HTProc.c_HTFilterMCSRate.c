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
struct rtllib_device {int* Regdot11TxHTOperationalRateSet; int /*<<< orphan*/  dev; scalar_t__ (* GetHalfNmodeSupportByAPsHandler ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HT_PickMCSRate (struct rtllib_device*,int*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 HTFilterMCSRate(struct rtllib_device *ieee, u8 *pSupportMCS,
			  u8 *pOperateMCS)
{

	u8 i;

	for (i = 0; i <= 15; i++)
		pOperateMCS[i] = ieee->Regdot11TxHTOperationalRateSet[i] &
				 pSupportMCS[i];

	HT_PickMCSRate(ieee, pOperateMCS);

	if (ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))
		pOperateMCS[1] = 0;

	for (i = 2; i <= 15; i++)
		pOperateMCS[i] = 0;

	return true;
}