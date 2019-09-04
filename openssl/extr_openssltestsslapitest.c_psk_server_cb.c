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
 unsigned int SSL_SESSION_get_master_key (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int find_session_cb_cnt ; 
 int /*<<< orphan*/  psk_server_cb_cnt ; 
 int /*<<< orphan*/ * serverpsk ; 
 int /*<<< orphan*/  srvid ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static unsigned int psk_server_cb(SSL *ssl, const char *identity,
                                  unsigned char *psk, unsigned int max_psk_len)
{
    unsigned int psklen = 0;

    psk_server_cb_cnt++;

    /* We should only ever be called a maximum of twice per connection */
    if (find_session_cb_cnt > 2)
        return 0;

    if (serverpsk == NULL)
        return 0;

    /* Identity should match that set by the client */
    if (strcmp(srvid, identity) != 0) {
        return 0;
    }

    /* We'll reuse the PSK we set up for TLSv1.3 */
    if (SSL_SESSION_get_master_key(serverpsk, NULL, 0) > max_psk_len)
        return 0;
    psklen = SSL_SESSION_get_master_key(serverpsk, psk, max_psk_len);

    return psklen;
}