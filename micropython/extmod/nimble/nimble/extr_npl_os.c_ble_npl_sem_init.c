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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  uint ;
struct ble_npl_sem {scalar_t__ count; } ;
typedef  int /*<<< orphan*/  ble_npl_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_NPL_OK ; 
 int /*<<< orphan*/  DEBUG_SEM_printf (char*,struct ble_npl_sem*,int /*<<< orphan*/ ) ; 

ble_npl_error_t ble_npl_sem_init(struct ble_npl_sem *sem, uint16_t tokens) {
    DEBUG_SEM_printf("ble_npl_sem_init(%p, %u)\n", sem, (uint)tokens);
    sem->count = tokens;
    return BLE_NPL_OK;
}