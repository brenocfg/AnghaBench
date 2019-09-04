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
struct ba_record {scalar_t__ bValid; } ;
struct rx_ts_record {struct ba_record RxAdmittedBARecord; } ;
struct rtllib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeActivateBAEntry (struct rtllib_device*,struct ba_record*) ; 

__attribute__((used)) static u8 RxTsDeleteBA(struct rtllib_device *ieee, struct rx_ts_record *pRxTs)
{
	struct ba_record *pBa = &pRxTs->RxAdmittedBARecord;
	u8			bSendDELBA = false;

	if (pBa->bValid) {
		DeActivateBAEntry(ieee, pBa);
		bSendDELBA = true;
	}

	return bSendDELBA;
}