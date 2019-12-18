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
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_read (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUFSIZE ; 
 int /*<<< orphan*/  EVP_MAC_final (int /*<<< orphan*/ *,unsigned char*,size_t*,size_t) ; 
 int /*<<< orphan*/  EVP_MAC_init (int /*<<< orphan*/ *) ; 
 size_t EVP_MAC_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_update (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static int do_mac(EVP_MAC_CTX *ctx, unsigned char *tmp, BIO *in,
                  unsigned char *out, size_t *out_len)
{
    int ret = 0;
    int i;
    size_t outsz = *out_len;

    if (!EVP_MAC_init(ctx))
        goto err;
    if (EVP_MAC_size(ctx) > outsz)
        goto end;
    while ((i = BIO_read(in, (char *)tmp, BUFSIZE)) != 0) {
        if (i < 0 || !EVP_MAC_update(ctx, tmp, i))
            goto err;
    }
end:
    if (!EVP_MAC_final(ctx, out, out_len, outsz))
        goto err;
    ret = 1;
err:
    return ret;
}