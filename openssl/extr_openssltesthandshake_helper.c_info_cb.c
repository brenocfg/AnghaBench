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
struct TYPE_2__ {int alert_sent; int alert_received; int /*<<< orphan*/  num_fatal_alerts_sent; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  TYPE_1__ HANDSHAKE_EX_DATA ;

/* Variables and functions */
 int SSL_CB_ALERT ; 
 int SSL_CB_WRITE ; 
 int /*<<< orphan*/  SSL_alert_desc_string (int) ; 
 int /*<<< orphan*/  SSL_alert_type_string (int) ; 
 scalar_t__ SSL_get_ex_data (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_data_idx ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void info_cb(const SSL *s, int where, int ret)
{
    if (where & SSL_CB_ALERT) {
        HANDSHAKE_EX_DATA *ex_data =
            (HANDSHAKE_EX_DATA*)(SSL_get_ex_data(s, ex_data_idx));
        if (where & SSL_CB_WRITE) {
            ex_data->alert_sent = ret;
            if (strcmp(SSL_alert_type_string(ret), "F") == 0
                || strcmp(SSL_alert_desc_string(ret), "CN") == 0)
                ex_data->num_fatal_alerts_sent++;
        } else {
            ex_data->alert_received = ret;
        }
    }
}