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
 int SSL_get_tlsext_status_ocsp_resp (int /*<<< orphan*/ *,unsigned char const**) ; 
 unsigned char const dummy_ocsp_resp_good_val ; 

__attribute__((used)) static int client_ocsp_cb(SSL *s, void *arg)
{
    const unsigned char *resp;
    int len;

    len = SSL_get_tlsext_status_ocsp_resp(s, &resp);
    if (len != 1 || *resp != dummy_ocsp_resp_good_val)
        return 0;

    return 1;
}