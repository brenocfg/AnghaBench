#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {TYPE_1__* PERIPHID; } ;
struct TYPE_3__ {int PERM; } ;

/* Variables and functions */
 TYPE_2__* NRF_SPU_S ; 
 int /*<<< orphan*/  NVIC_DisableIRQ (size_t) ; 
 int /*<<< orphan*/  NVIC_SetTargetState (size_t) ; 
 int SPU_PERIPHID_PERM_LOCK_Locked ; 
 int SPU_PERIPHID_PERM_LOCK_Pos ; 
 int SPU_PERIPHID_PERM_PRESENT_IsPresent ; 
 int SPU_PERIPHID_PERM_PRESENT_Pos ; 
 int SPU_PERIPHID_PERM_SECATTR_NonSecure ; 
 int SPU_PERIPHID_PERM_SECATTR_Pos ; 

__attribute__((used)) static void peripheral_setup(uint8_t peripheral_id)
{
    NVIC_DisableIRQ(peripheral_id);
    uint32_t perm = 0;
    perm |= (SPU_PERIPHID_PERM_PRESENT_IsPresent << SPU_PERIPHID_PERM_PRESENT_Pos);
    perm |= (SPU_PERIPHID_PERM_SECATTR_NonSecure << SPU_PERIPHID_PERM_SECATTR_Pos);
    perm |= (SPU_PERIPHID_PERM_LOCK_Locked << SPU_PERIPHID_PERM_LOCK_Pos);
    NRF_SPU_S->PERIPHID[peripheral_id].PERM = perm;

    NVIC_SetTargetState(peripheral_id);
}