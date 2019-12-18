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
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_SESSION_up_ref (int /*<<< orphan*/ *) ; 
 int find_session_cb_cnt ; 
 int /*<<< orphan*/ * serverpsk ; 
 int /*<<< orphan*/  srvid ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static int find_session_cb(SSL *ssl, const unsigned char *identity,
                           size_t identity_len, SSL_SESSION **sess)
{
    find_session_cb_cnt++;

    /* We should only ever be called a maximum of twice per connection */
    if (find_session_cb_cnt > 2)
        return 0;

    if (serverpsk == NULL)
        return 0;

    /* Identity should match that set by the client */
    if (strlen(srvid) != identity_len
            || strncmp(srvid, (const char *)identity, identity_len) != 0) {
        /* No PSK found, continue but without a PSK */
        *sess = NULL;
        return 1;
    }

    SSL_SESSION_up_ref(serverpsk);
    *sess = serverpsk;

    return 1;
}