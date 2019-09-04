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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  scalar_t__ _i16 ;

/* Variables and functions */
 int HAL_NVIC_INT_CTRL_REG ; 
 int HAL_VECTACTIVE_MASK ; 
 scalar_t__ IRQ_STATE_ENABLED ; 
 scalar_t__ SL_EAGAIN ; 
 scalar_t__ TELNET_TX_RETRIES_MAX ; 
 int /*<<< orphan*/  TELNET_WAIT_TIME_MS ; 
 int /*<<< orphan*/  mp_hal_delay_ms (int /*<<< orphan*/ ) ; 
 scalar_t__ query_irq () ; 
 scalar_t__ sl_Send (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool telnet_send_with_retries (int16_t sd, const void *pBuf, int16_t len) {
    int32_t retries = 0;
    uint32_t delay = TELNET_WAIT_TIME_MS;
    // only if we are not within interrupt context and interrupts are enabled
    if ((HAL_NVIC_INT_CTRL_REG & HAL_VECTACTIVE_MASK) == 0 && query_irq() == IRQ_STATE_ENABLED) {
        do {
            _i16 result = sl_Send(sd, pBuf, len, 0);
            if (result > 0) {
                return true;
            }
            else if (SL_EAGAIN != result) {
                return false;
            }
            // start with the default delay and increment it on each retry
            mp_hal_delay_ms(delay++);
        } while (++retries <= TELNET_TX_RETRIES_MAX);
    }
    return false;
}