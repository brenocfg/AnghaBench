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
typedef  int /*<<< orphan*/  tWriteWlanPin ;
typedef  int /*<<< orphan*/  tWlanReadInteruptPin ;
typedef  int /*<<< orphan*/  tWlanInterruptEnable ;
typedef  int /*<<< orphan*/  tWlanInterruptDisable ;
typedef  int /*<<< orphan*/  tWlanCB ;
typedef  int /*<<< orphan*/  tFWPatches ;
typedef  int /*<<< orphan*/  tDriverPatches ;
typedef  int /*<<< orphan*/  tBootLoaderPatches ;
struct TYPE_2__ {int InformHostOnTxComplete; int /*<<< orphan*/  sWlanCB; int /*<<< orphan*/  WriteWlanPin; int /*<<< orphan*/  WlanInterruptDisable; int /*<<< orphan*/  WlanInterruptEnable; int /*<<< orphan*/  ReadWlanInterruptPin; int /*<<< orphan*/  sBootLoaderPatches; int /*<<< orphan*/  sDriverPatches; int /*<<< orphan*/  sFWPatches; } ;

/* Variables and functions */
 TYPE_1__ tSLInformation ; 

void wlan_init(		tWlanCB	 	sWlanCB,
	tFWPatches sFWPatches,
	tDriverPatches sDriverPatches,
	tBootLoaderPatches sBootLoaderPatches,
	tWlanReadInteruptPin  sReadWlanInterruptPin,
	tWlanInterruptEnable  sWlanInterruptEnable,
	tWlanInterruptDisable sWlanInterruptDisable,
	tWriteWlanPin         sWriteWlanPin)
{

	tSLInformation.sFWPatches = sFWPatches;
	tSLInformation.sDriverPatches = sDriverPatches;
	tSLInformation.sBootLoaderPatches = sBootLoaderPatches;

	// init io callback
	tSLInformation.ReadWlanInterruptPin = sReadWlanInterruptPin;
	tSLInformation.WlanInterruptEnable  = sWlanInterruptEnable;
	tSLInformation.WlanInterruptDisable = sWlanInterruptDisable;
	tSLInformation.WriteWlanPin = sWriteWlanPin;

	//init asynchronous events callback
	tSLInformation.sWlanCB= sWlanCB;

	// By default TX Complete events are routed to host too
	tSLInformation.InformHostOnTxComplete = 1;
}