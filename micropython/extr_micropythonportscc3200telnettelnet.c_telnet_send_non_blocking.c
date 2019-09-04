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
typedef  int /*<<< orphan*/  telnet_result_t ;
typedef  scalar_t__ int16_t ;
typedef  int /*<<< orphan*/  _i16 ;
struct TYPE_2__ {scalar_t__ txRetries; int /*<<< orphan*/  n_sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_TELNET_RESULT_AGAIN ; 
 int /*<<< orphan*/  E_TELNET_RESULT_FAILED ; 
 int /*<<< orphan*/  E_TELNET_RESULT_OK ; 
 scalar_t__ SL_EAGAIN ; 
 scalar_t__ TELNET_TX_RETRIES_MAX ; 
 scalar_t__ sl_Send (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ telnet_data ; 
 int /*<<< orphan*/  telnet_reset () ; 

__attribute__((used)) static telnet_result_t telnet_send_non_blocking (void *data, _i16 Len) {
    int16_t result = sl_Send(telnet_data.n_sd, data, Len, 0);

    if (result > 0) {
        telnet_data.txRetries = 0;
        return E_TELNET_RESULT_OK;
    }
    else if ((TELNET_TX_RETRIES_MAX >= ++telnet_data.txRetries) && (result == SL_EAGAIN)) {
        return E_TELNET_RESULT_AGAIN;
    }
    else {
        // error
        telnet_reset();
        return E_TELNET_RESULT_FAILED;
    }
}