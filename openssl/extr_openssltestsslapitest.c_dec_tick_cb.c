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
typedef  int SSL_TICKET_STATUS ;
typedef  int /*<<< orphan*/  SSL_TICKET_RETURN ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int SSL_SESSION_get0_ticket_appdata (int /*<<< orphan*/ *,void**,size_t*) ; 
 int SSL_TICKET_EMPTY ; 
#define  SSL_TICKET_NO_DECRYPT 130 
 int /*<<< orphan*/  SSL_TICKET_RETURN_ABORT ; 
 int /*<<< orphan*/  SSL_TICKET_RETURN_IGNORE_RENEW ; 
 int /*<<< orphan*/  SSL_TICKET_RETURN_USE ; 
 int /*<<< orphan*/  SSL_TICKET_RETURN_USE_RENEW ; 
#define  SSL_TICKET_SUCCESS 129 
#define  SSL_TICKET_SUCCESS_RENEW 128 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int /*<<< orphan*/  appdata ; 
 int dec_tick_called ; 
 int /*<<< orphan*/  memcmp (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick_dec_ret ; 
 scalar_t__ tick_key_cb_called ; 

__attribute__((used)) static SSL_TICKET_RETURN dec_tick_cb(SSL *s, SSL_SESSION *ss,
                                     const unsigned char *keyname,
                                     size_t keyname_length,
                                     SSL_TICKET_STATUS status,
                                     void *arg)
{
    void *tickdata;
    size_t tickdlen;

    dec_tick_called = 1;

    if (status == SSL_TICKET_EMPTY)
        return SSL_TICKET_RETURN_IGNORE_RENEW;

    if (!TEST_true(status == SSL_TICKET_SUCCESS
                   || status == SSL_TICKET_SUCCESS_RENEW))
        return SSL_TICKET_RETURN_ABORT;

    if (!TEST_true(SSL_SESSION_get0_ticket_appdata(ss, &tickdata,
                                                   &tickdlen))
            || !TEST_size_t_eq(tickdlen, strlen(appdata))
            || !TEST_int_eq(memcmp(tickdata, appdata, tickdlen), 0))
        return SSL_TICKET_RETURN_ABORT;

    if (tick_key_cb_called)  {
        /* Don't change what the ticket key callback wanted to do */
        switch (status) {
        case SSL_TICKET_NO_DECRYPT:
            return SSL_TICKET_RETURN_IGNORE_RENEW;

        case SSL_TICKET_SUCCESS:
            return SSL_TICKET_RETURN_USE;

        case SSL_TICKET_SUCCESS_RENEW:
            return SSL_TICKET_RETURN_USE_RENEW;

        default:
            return SSL_TICKET_RETURN_ABORT;
        }
    }
    return tick_dec_ret;

}