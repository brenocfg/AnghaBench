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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint ;
struct ble_npl_sem {scalar_t__ count; } ;
typedef  scalar_t__ ble_npl_time_t ;
typedef  int /*<<< orphan*/  ble_npl_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_NPL_OK ; 
 int /*<<< orphan*/  BLE_NPL_TIMEOUT ; 
 int /*<<< orphan*/  DEBUG_SEM_printf (char*,...) ; 
 int /*<<< orphan*/  __WFI () ; 
 scalar_t__ mp_hal_ticks_ms () ; 
 int /*<<< orphan*/  printf (char*) ; 

ble_npl_error_t ble_npl_sem_pend(struct ble_npl_sem *sem, ble_npl_time_t timeout) {
    DEBUG_SEM_printf("ble_npl_sem_pend(%p, %u) count=%u\n", sem, (uint)timeout, (uint)sem->count);
    if (sem->count == 0) {
        uint32_t t0 = mp_hal_ticks_ms();
        while (sem->count == 0 && mp_hal_ticks_ms() - t0 < timeout) {
            extern void nimble_uart_process(void);
            nimble_uart_process();
            if (sem->count != 0) {
                break;
            }
            __WFI();
        }
        if (sem->count == 0) {
            printf("timeout\n");
            return BLE_NPL_TIMEOUT;
        }
        DEBUG_SEM_printf("got response in %u ms\n", (int)(mp_hal_ticks_ms() - t0));
    }
    sem->count -= 1;
    return BLE_NPL_OK;
}