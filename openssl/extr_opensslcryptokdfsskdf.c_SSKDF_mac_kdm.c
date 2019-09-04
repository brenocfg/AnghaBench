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
typedef  int /*<<< orphan*/  mac_buf ;
typedef  int /*<<< orphan*/  c ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;
typedef  int /*<<< orphan*/  EVP_MAC ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_KEY ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_MD ; 
 scalar_t__ EVP_MAC_CTX_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MAC_CTX_new (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_MAC_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,...) ; 
 int /*<<< orphan*/  EVP_MAC_final (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_init (int /*<<< orphan*/ *) ; 
 size_t EVP_MAC_size (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_MAC_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 size_t SSKDF_MAX_INLEN ; 
 int /*<<< orphan*/  kmac_init (int /*<<< orphan*/ *,unsigned char const*,size_t,size_t,size_t,unsigned char**) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static int SSKDF_mac_kdm(const EVP_MAC *kdf_mac, const EVP_MD *hmac_md,
                         const unsigned char *kmac_custom,
                         size_t kmac_custom_len, size_t kmac_out_len,
                         const unsigned char *salt, size_t salt_len,
                         const unsigned char *z, size_t z_len,
                         const unsigned char *info, size_t info_len,
                         unsigned char *derived_key, size_t derived_key_len)
{
    int ret = 0;
    size_t counter, out_len, len;
    unsigned char c[4];
    unsigned char mac_buf[EVP_MAX_MD_SIZE];
    unsigned char *out = derived_key;
    EVP_MAC_CTX *ctx = NULL, *ctx_init = NULL;
    unsigned char *mac = mac_buf, *kmac_buffer = NULL;

    if (z_len > SSKDF_MAX_INLEN || info_len > SSKDF_MAX_INLEN
            || derived_key_len > SSKDF_MAX_INLEN
            || derived_key_len == 0)
        return 0;

    ctx = EVP_MAC_CTX_new(kdf_mac);
    ctx_init = EVP_MAC_CTX_new(kdf_mac);
    if (ctx == NULL || ctx_init == NULL)
        goto end;
    if (hmac_md != NULL &&
            EVP_MAC_ctrl(ctx_init, EVP_MAC_CTRL_SET_MD, hmac_md) <= 0)
        goto end;

    if (EVP_MAC_ctrl(ctx_init, EVP_MAC_CTRL_SET_KEY, salt, salt_len) <= 0)
        goto end;

    if (!kmac_init(ctx_init, kmac_custom, kmac_custom_len, kmac_out_len,
                   derived_key_len, &kmac_buffer))
        goto end;
    if (kmac_buffer != NULL)
        mac = kmac_buffer;

    if (!EVP_MAC_init(ctx_init))
        goto end;

    out_len = EVP_MAC_size(ctx_init); /* output size */
    if (out_len <= 0)
        goto end;
    len = derived_key_len;

    for (counter = 1;; counter++) {
        c[0] = (unsigned char)((counter >> 24) & 0xff);
        c[1] = (unsigned char)((counter >> 16) & 0xff);
        c[2] = (unsigned char)((counter >> 8) & 0xff);
        c[3] = (unsigned char)(counter & 0xff);

        if (!(EVP_MAC_CTX_copy(ctx, ctx_init)
                && EVP_MAC_update(ctx, c, sizeof(c))
                && EVP_MAC_update(ctx, z, z_len)
                && EVP_MAC_update(ctx, info, info_len)))
            goto end;
        if (len >= out_len) {
            if (!EVP_MAC_final(ctx, out, NULL))
                goto end;
            out += out_len;
            len -= out_len;
            if (len == 0)
                break;
        } else {
            if (!EVP_MAC_final(ctx, mac, NULL))
                goto end;
            memcpy(out, mac, len);
            break;
        }
    }
    ret = 1;
end:
    if (kmac_buffer != NULL)
        OPENSSL_clear_free(kmac_buffer, kmac_out_len);
    else
        OPENSSL_cleanse(mac_buf, sizeof(mac_buf));

    EVP_MAC_CTX_free(ctx);
    EVP_MAC_CTX_free(ctx_init);
    return ret;
}