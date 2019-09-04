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
typedef  int /*<<< orphan*/  TS_RESP_CTX ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  TS_INFO_ADD_INFO_NOT_AVAILABLE ; 
 int /*<<< orphan*/  TS_RESP_CTX_add_failure_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_status_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TS_STATUS_REJECTION ; 
 int /*<<< orphan*/ * next_serial (char const*) ; 
 int /*<<< orphan*/  save_ts_serial (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ASN1_INTEGER *serial_cb(TS_RESP_CTX *ctx, void *data)
{
    const char *serial_file = (const char *)data;
    ASN1_INTEGER *serial = next_serial(serial_file);

    if (serial == NULL) {
        TS_RESP_CTX_set_status_info(ctx, TS_STATUS_REJECTION,
                                    "Error during serial number "
                                    "generation.");
        TS_RESP_CTX_add_failure_info(ctx, TS_INFO_ADD_INFO_NOT_AVAILABLE);
    } else {
        save_ts_serial(serial_file, serial);
    }

    return serial;
}