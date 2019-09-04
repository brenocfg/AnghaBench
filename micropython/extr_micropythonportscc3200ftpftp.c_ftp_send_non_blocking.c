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
typedef  scalar_t__ int16_t ;
typedef  int /*<<< orphan*/  ftp_result_t ;
typedef  int /*<<< orphan*/  _i16 ;
struct TYPE_2__ {scalar_t__ txRetries; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_FTP_RESULT_CONTINUE ; 
 int /*<<< orphan*/  E_FTP_RESULT_FAILED ; 
 int /*<<< orphan*/  E_FTP_RESULT_OK ; 
 scalar_t__ FTP_TX_RETRIES_MAX ; 
 scalar_t__ SL_EAGAIN ; 
 TYPE_1__ ftp_data ; 
 int /*<<< orphan*/  ftp_reset () ; 
 scalar_t__ sl_Send (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ftp_result_t ftp_send_non_blocking (_i16 sd, void *data, _i16 Len) {
    int16_t result = sl_Send(sd, data, Len, 0);

    if (result > 0) {
        ftp_data.txRetries = 0;
        return E_FTP_RESULT_OK;
    }
    else if ((FTP_TX_RETRIES_MAX >= ++ftp_data.txRetries) && (result == SL_EAGAIN)) {
        return E_FTP_RESULT_CONTINUE;
    }
    else {
        // error
        ftp_reset();
        return E_FTP_RESULT_FAILED;
    }
}