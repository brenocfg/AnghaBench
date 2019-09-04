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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,...) ; 
 int SSL_CB_ALERT ; 
 int SSL_CB_EXIT ; 
 int SSL_CB_LOOP ; 
 int SSL_CB_READ ; 
 int SSL_ST_ACCEPT ; 
 int SSL_ST_CONNECT ; 
 int SSL_ST_MASK ; 
 int /*<<< orphan*/  SSL_alert_desc_string_long (int) ; 
 int /*<<< orphan*/  SSL_alert_type_string_long (int) ; 
 int /*<<< orphan*/  SSL_state_string_long (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bio_err ; 

void apps_ssl_info_callback(const SSL *s, int where, int ret)
{
    const char *str;
    int w;

    w = where & ~SSL_ST_MASK;

    if (w & SSL_ST_CONNECT)
        str = "SSL_connect";
    else if (w & SSL_ST_ACCEPT)
        str = "SSL_accept";
    else
        str = "undefined";

    if (where & SSL_CB_LOOP) {
        BIO_printf(bio_err, "%s:%s\n", str, SSL_state_string_long(s));
    } else if (where & SSL_CB_ALERT) {
        str = (where & SSL_CB_READ) ? "read" : "write";
        BIO_printf(bio_err, "SSL3 alert %s:%s:%s\n",
                   str,
                   SSL_alert_type_string_long(ret),
                   SSL_alert_desc_string_long(ret));
    } else if (where & SSL_CB_EXIT) {
        if (ret == 0)
            BIO_printf(bio_err, "%s:failed in %s\n",
                       str, SSL_state_string_long(s));
        else if (ret < 0)
            BIO_printf(bio_err, "%s:error in %s\n",
                       str, SSL_state_string_long(s));
    }
}