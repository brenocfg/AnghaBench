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
typedef  scalar_t__ _i16 ;
struct TYPE_2__ {scalar_t__ timeout; int /*<<< orphan*/  n_sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_TELNET_RESULT_AGAIN ; 
 int /*<<< orphan*/  E_TELNET_RESULT_FAILED ; 
 int /*<<< orphan*/  E_TELNET_RESULT_OK ; 
 scalar_t__ SL_EAGAIN ; 
 scalar_t__ sl_Recv (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ telnet_data ; 
 int /*<<< orphan*/  telnet_parse_input (void*,scalar_t__*) ; 
 int /*<<< orphan*/  telnet_reset () ; 

__attribute__((used)) static telnet_result_t telnet_recv_text_non_blocking (void *buff, _i16 Maxlen, _i16 *rxLen) {
    *rxLen = sl_Recv(telnet_data.n_sd, buff, Maxlen, 0);
    // if there's data received, parse it
    if (*rxLen > 0) {
        telnet_data.timeout = 0;
        telnet_parse_input (buff, rxLen);
        if (*rxLen > 0) {
            return E_TELNET_RESULT_OK;
        }
    }
    else if (*rxLen != SL_EAGAIN) {
        // error
        telnet_reset();
        return E_TELNET_RESULT_FAILED;
    }
    return E_TELNET_RESULT_AGAIN;
}