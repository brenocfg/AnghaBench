#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* d1; } ;
struct TYPE_5__ {size_t cookie_len; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 int /*<<< orphan*/  MSG_PROCESS_FINISHED_READING ; 
 int /*<<< orphan*/  PACKET_copy_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  PACKET_forward (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_F_DTLS_PROCESS_HELLO_VERIFY ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_LENGTH_TOO_LONG ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

MSG_PROCESS_RETURN dtls_process_hello_verify(SSL *s, PACKET *pkt)
{
    size_t cookie_len;
    PACKET cookiepkt;

    if (!PACKET_forward(pkt, 2)
        || !PACKET_get_length_prefixed_1(pkt, &cookiepkt)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_DTLS_PROCESS_HELLO_VERIFY,
                 SSL_R_LENGTH_MISMATCH);
        return MSG_PROCESS_ERROR;
    }

    cookie_len = PACKET_remaining(&cookiepkt);
    if (cookie_len > sizeof(s->d1->cookie)) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_DTLS_PROCESS_HELLO_VERIFY,
                 SSL_R_LENGTH_TOO_LONG);
        return MSG_PROCESS_ERROR;
    }

    if (!PACKET_copy_bytes(&cookiepkt, s->d1->cookie, cookie_len)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_DTLS_PROCESS_HELLO_VERIFY,
                 SSL_R_LENGTH_MISMATCH);
        return MSG_PROCESS_ERROR;
    }
    s->d1->cookie_len = cookie_len;

    return MSG_PROCESS_FINISHED_READING;
}