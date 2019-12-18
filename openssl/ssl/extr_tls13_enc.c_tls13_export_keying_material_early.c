#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  exporterlabel ;
struct TYPE_9__ {scalar_t__ max_early_data; } ;
struct TYPE_12__ {TYPE_1__ ext; } ;
struct TYPE_11__ {scalar_t__ max_early_data; unsigned char* early_exporter_master_secret; TYPE_8__* session; TYPE_8__* psksession; int /*<<< orphan*/  server; } ;
struct TYPE_10__ {int /*<<< orphan*/  algorithm2; } ;
typedef  TYPE_2__ SSL_CIPHER ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 scalar_t__ EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 scalar_t__ EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 TYPE_2__* SSL_SESSION_get0_cipher (TYPE_8__*) ; 
 int /*<<< orphan*/  ossl_statem_export_early_allowed (TYPE_3__*) ; 
 int /*<<< orphan*/ * ssl_md (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls13_hkdf_expand (TYPE_3__*,int /*<<< orphan*/  const*,unsigned char*,unsigned char const*,int,unsigned char*,unsigned int,unsigned char*,size_t,int /*<<< orphan*/ ) ; 

int tls13_export_keying_material_early(SSL *s, unsigned char *out, size_t olen,
                                       const char *label, size_t llen,
                                       const unsigned char *context,
                                       size_t contextlen)
{
#ifdef CHARSET_EBCDIC
  static const unsigned char exporterlabel[] = {0x65, 0x78, 0x70, 0x6F, 0x72, 0x74, 0x65, 0x72, 0x00};
#else
  static const unsigned char exporterlabel[] = "exporter";
#endif
    unsigned char exportsecret[EVP_MAX_MD_SIZE];
    unsigned char hash[EVP_MAX_MD_SIZE], data[EVP_MAX_MD_SIZE];
    const EVP_MD *md;
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    unsigned int hashsize, datalen;
    int ret = 0;
    const SSL_CIPHER *sslcipher;

    if (ctx == NULL || !ossl_statem_export_early_allowed(s))
        goto err;

    if (!s->server && s->max_early_data > 0
            && s->session->ext.max_early_data == 0)
        sslcipher = SSL_SESSION_get0_cipher(s->psksession);
    else
        sslcipher = SSL_SESSION_get0_cipher(s->session);

    md = ssl_md(sslcipher->algorithm2);

    /*
     * Calculate the hash value and store it in |data|. The reason why
     * the empty string is used is that the definition of TLS-Exporter
     * is like so:
     *
     * TLS-Exporter(label, context_value, key_length) =
     *     HKDF-Expand-Label(Derive-Secret(Secret, label, ""),
     *                       "exporter", Hash(context_value), key_length)
     *
     * Derive-Secret(Secret, Label, Messages) =
     *       HKDF-Expand-Label(Secret, Label,
     *                         Transcript-Hash(Messages), Hash.length)
     *
     * Here Transcript-Hash is the cipher suite hash algorithm.
     */
    if (EVP_DigestInit_ex(ctx, md, NULL) <= 0
            || EVP_DigestUpdate(ctx, context, contextlen) <= 0
            || EVP_DigestFinal_ex(ctx, hash, &hashsize) <= 0
            || EVP_DigestInit_ex(ctx, md, NULL) <= 0
            || EVP_DigestFinal_ex(ctx, data, &datalen) <= 0
            || !tls13_hkdf_expand(s, md, s->early_exporter_master_secret,
                                  (const unsigned char *)label, llen,
                                  data, datalen, exportsecret, hashsize, 0)
            || !tls13_hkdf_expand(s, md, exportsecret, exporterlabel,
                                  sizeof(exporterlabel) - 1, hash, hashsize,
                                  out, olen, 0))
        goto err;

    ret = 1;
 err:
    EVP_MD_CTX_free(ctx);
    return ret;
}