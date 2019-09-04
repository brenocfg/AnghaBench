#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_6__ {TYPE_1__* spurChans; } ;
struct TYPE_7__ {TYPE_2__ modalHeader; } ;
struct TYPE_8__ {TYPE_3__ map4k; } ;
struct ath_hw {TYPE_4__ eeprom; } ;
struct TYPE_5__ {int /*<<< orphan*/  spurChan; } ;

/* Variables and functions */
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 ath9k_hw_4k_get_spur_channel(struct ath_hw *ah, u16 i, bool is2GHz)
{
	return le16_to_cpu(ah->eeprom.map4k.modalHeader.spurChans[i].spurChan);
}