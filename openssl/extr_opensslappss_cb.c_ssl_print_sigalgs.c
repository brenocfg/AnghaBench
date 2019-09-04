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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int NID_undef ; 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 scalar_t__ SSL_get_peer_signature_nid (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ SSL_get_peer_signature_type_nid (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  SSL_is_server (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_print_sigalgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_sigtype (int) ; 
 int /*<<< orphan*/  ssl_print_client_cert_types (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ssl_print_sigalgs(BIO *out, SSL *s)
{
    int nid;
    if (!SSL_is_server(s))
        ssl_print_client_cert_types(out, s);
    do_print_sigalgs(out, s, 0);
    do_print_sigalgs(out, s, 1);
    if (SSL_get_peer_signature_nid(s, &nid) && nid != NID_undef)
        BIO_printf(out, "Peer signing digest: %s\n", OBJ_nid2sn(nid));
    if (SSL_get_peer_signature_type_nid(s, &nid))
        BIO_printf(out, "Peer signature type: %s\n", get_sigtype(nid));
    return 1;
}