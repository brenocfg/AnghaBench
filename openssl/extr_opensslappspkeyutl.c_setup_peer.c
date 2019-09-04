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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int EVP_PKEY_derive_set_peer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int FORMAT_ENGINE ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * load_pubkey (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int setup_peer(EVP_PKEY_CTX *ctx, int peerform, const char *file,
                      ENGINE *e)
{
    EVP_PKEY *peer = NULL;
    ENGINE *engine = NULL;
    int ret;

    if (peerform == FORMAT_ENGINE)
        engine = e;
    peer = load_pubkey(file, peerform, 0, NULL, engine, "Peer Key");
    if (peer == NULL) {
        BIO_printf(bio_err, "Error reading peer key %s\n", file);
        ERR_print_errors(bio_err);
        return 0;
    }

    ret = EVP_PKEY_derive_set_peer(ctx, peer);

    EVP_PKEY_free(peer);
    if (ret <= 0)
        ERR_print_errors(bio_err);
    return ret;
}