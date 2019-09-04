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
 int BIO_snprintf (char*,unsigned int,char*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  psk_key ; 
 int psk_key2bn (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static unsigned int psk_client_callback(SSL *ssl, const char *hint,
                                        char *identity,
                                        unsigned int max_identity_len,
                                        unsigned char *psk,
                                        unsigned int max_psk_len)
{
    int ret;
    unsigned int psk_len = 0;

    ret = BIO_snprintf(identity, max_identity_len, "Client_identity");
    if (ret < 0)
        goto out_err;
    if (debug)
        fprintf(stderr, "client: created identity '%s' len=%d\n", identity,
                ret);
    ret = psk_key2bn(psk_key, psk, max_psk_len);
    if (ret < 0)
        goto out_err;
    psk_len = ret;
 out_err:
    return psk_len;
}