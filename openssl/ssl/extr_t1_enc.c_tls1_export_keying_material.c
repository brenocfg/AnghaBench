#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned char const* client_random; unsigned char const* server_random; } ;
struct TYPE_8__ {TYPE_2__* session; TYPE_1__ s3; } ;
struct TYPE_7__ {int /*<<< orphan*/  master_key_length; int /*<<< orphan*/  master_key; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int SSL3_RANDOM_SIZE ; 
 int /*<<< orphan*/  SSL_F_TLS1_EXPORT_KEYING_MATERIAL ; 
 int /*<<< orphan*/  SSL_R_TLS_ILLEGAL_EXPORTER_LABEL ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS_MD_CLIENT_FINISH_CONST ; 
 int /*<<< orphan*/  TLS_MD_CLIENT_FINISH_CONST_SIZE ; 
 int /*<<< orphan*/  TLS_MD_EXTENDED_MASTER_SECRET_CONST ; 
 int /*<<< orphan*/  TLS_MD_EXTENDED_MASTER_SECRET_CONST_SIZE ; 
 int /*<<< orphan*/  TLS_MD_KEY_EXPANSION_CONST ; 
 int /*<<< orphan*/  TLS_MD_KEY_EXPANSION_CONST_SIZE ; 
 int /*<<< orphan*/  TLS_MD_MASTER_SECRET_CONST ; 
 int /*<<< orphan*/  TLS_MD_MASTER_SECRET_CONST_SIZE ; 
 int /*<<< orphan*/  TLS_MD_SERVER_FINISH_CONST ; 
 int /*<<< orphan*/  TLS_MD_SERVER_FINISH_CONST_SIZE ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int tls1_PRF (TYPE_3__*,unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t,int /*<<< orphan*/ ) ; 

int tls1_export_keying_material(SSL *s, unsigned char *out, size_t olen,
                                const char *label, size_t llen,
                                const unsigned char *context,
                                size_t contextlen, int use_context)
{
    unsigned char *val = NULL;
    size_t vallen = 0, currentvalpos;
    int rv;

    /*
     * construct PRF arguments we construct the PRF argument ourself rather
     * than passing separate values into the TLS PRF to ensure that the
     * concatenation of values does not create a prohibited label.
     */
    vallen = llen + SSL3_RANDOM_SIZE * 2;
    if (use_context) {
        vallen += 2 + contextlen;
    }

    val = OPENSSL_malloc(vallen);
    if (val == NULL)
        goto err2;
    currentvalpos = 0;
    memcpy(val + currentvalpos, (unsigned char *)label, llen);
    currentvalpos += llen;
    memcpy(val + currentvalpos, s->s3.client_random, SSL3_RANDOM_SIZE);
    currentvalpos += SSL3_RANDOM_SIZE;
    memcpy(val + currentvalpos, s->s3.server_random, SSL3_RANDOM_SIZE);
    currentvalpos += SSL3_RANDOM_SIZE;

    if (use_context) {
        val[currentvalpos] = (contextlen >> 8) & 0xff;
        currentvalpos++;
        val[currentvalpos] = contextlen & 0xff;
        currentvalpos++;
        if ((contextlen > 0) || (context != NULL)) {
            memcpy(val + currentvalpos, context, contextlen);
        }
    }

    /*
     * disallow prohibited labels note that SSL3_RANDOM_SIZE > max(prohibited
     * label len) = 15, so size of val > max(prohibited label len) = 15 and
     * the comparisons won't have buffer overflow
     */
    if (memcmp(val, TLS_MD_CLIENT_FINISH_CONST,
               TLS_MD_CLIENT_FINISH_CONST_SIZE) == 0)
        goto err1;
    if (memcmp(val, TLS_MD_SERVER_FINISH_CONST,
               TLS_MD_SERVER_FINISH_CONST_SIZE) == 0)
        goto err1;
    if (memcmp(val, TLS_MD_MASTER_SECRET_CONST,
               TLS_MD_MASTER_SECRET_CONST_SIZE) == 0)
        goto err1;
    if (memcmp(val, TLS_MD_EXTENDED_MASTER_SECRET_CONST,
               TLS_MD_EXTENDED_MASTER_SECRET_CONST_SIZE) == 0)
        goto err1;
    if (memcmp(val, TLS_MD_KEY_EXPANSION_CONST,
               TLS_MD_KEY_EXPANSION_CONST_SIZE) == 0)
        goto err1;

    rv = tls1_PRF(s,
                  val, vallen,
                  NULL, 0,
                  NULL, 0,
                  NULL, 0,
                  NULL, 0,
                  s->session->master_key, s->session->master_key_length,
                  out, olen, 0);

    goto ret;
 err1:
    SSLerr(SSL_F_TLS1_EXPORT_KEYING_MATERIAL, SSL_R_TLS_ILLEGAL_EXPORTER_LABEL);
    rv = 0;
    goto ret;
 err2:
    SSLerr(SSL_F_TLS1_EXPORT_KEYING_MATERIAL, ERR_R_MALLOC_FAILURE);
    rv = 0;
 ret:
    OPENSSL_clear_free(val, vallen);
    return rv;
}