#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* new_cipher; } ;
struct TYPE_9__ {TYPE_2__ tmp; } ;
struct TYPE_10__ {int verify_mode; scalar_t__ post_handshake_auth; int certreqs_sent; TYPE_3__ s3; } ;
struct TYPE_7__ {int algorithm_auth; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_IS_TLS13 (TYPE_4__*) ; 
 scalar_t__ SSL_PHA_REQUEST_PENDING ; 
 int SSL_VERIFY_CLIENT_ONCE ; 
 int SSL_VERIFY_FAIL_IF_NO_PEER_CERT ; 
 int SSL_VERIFY_PEER ; 
 int SSL_VERIFY_POST_HANDSHAKE ; 
 int SSL_aNULL ; 
 int SSL_aPSK ; 
 int SSL_aSRP ; 

int send_certificate_request(SSL *s)
{
    if (
           /* don't request cert unless asked for it: */
           s->verify_mode & SSL_VERIFY_PEER
           /*
            * don't request if post-handshake-only unless doing
            * post-handshake in TLSv1.3:
            */
           && (!SSL_IS_TLS13(s) || !(s->verify_mode & SSL_VERIFY_POST_HANDSHAKE)
               || s->post_handshake_auth == SSL_PHA_REQUEST_PENDING)
           /*
            * if SSL_VERIFY_CLIENT_ONCE is set, don't request cert
            * a second time:
            */
           && (s->certreqs_sent < 1 ||
               !(s->verify_mode & SSL_VERIFY_CLIENT_ONCE))
           /*
            * never request cert in anonymous ciphersuites (see
            * section "Certificate request" in SSL 3 drafts and in
            * RFC 2246):
            */
           && (!(s->s3.tmp.new_cipher->algorithm_auth & SSL_aNULL)
               /*
                * ... except when the application insists on
                * verification (against the specs, but statem_clnt.c accepts
                * this for SSL 3)
                */
               || (s->verify_mode & SSL_VERIFY_FAIL_IF_NO_PEER_CERT))
           /* don't request certificate for SRP auth */
           && !(s->s3.tmp.new_cipher->algorithm_auth & SSL_aSRP)
           /*
            * With normal PSK Certificates and Certificate Requests
            * are omitted
            */
           && !(s->s3.tmp.new_cipher->algorithm_auth & SSL_aPSK)) {
        return 1;
    }

    return 0;
}