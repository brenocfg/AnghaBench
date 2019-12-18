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
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
#define  SSL_TICKET_EMPTY 131 
#define  SSL_TICKET_NO_DECRYPT 130 
 int SSL_TICKET_RETURN_ABORT ; 
 int SSL_TICKET_RETURN_IGNORE_RENEW ; 
 int SSL_TICKET_RETURN_USE ; 
 int SSL_TICKET_RETURN_USE_RENEW ; 
#define  SSL_TICKET_SUCCESS 129 
#define  SSL_TICKET_SUCCESS_RENEW 128 

__attribute__((used)) static int decrypt_session_ticket_cb(SSL *s, SSL_SESSION *ss,
                                     const unsigned char *keyname,
                                     size_t keyname_len,
                                     SSL_TICKET_STATUS status,
                                     void *arg)
{
    switch (status) {
    case SSL_TICKET_EMPTY:
    case SSL_TICKET_NO_DECRYPT:
        return SSL_TICKET_RETURN_IGNORE_RENEW;
    case SSL_TICKET_SUCCESS:
        return SSL_TICKET_RETURN_USE;
    case SSL_TICKET_SUCCESS_RENEW:
        return SSL_TICKET_RETURN_USE_RENEW;
    default:
        break;
    }
    return SSL_TICKET_RETURN_ABORT;
}