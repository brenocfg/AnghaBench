#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ encode; int buf_len; int buf_off; int tmp_len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  base64; int /*<<< orphan*/ * tmp; } ;
typedef  TYPE_1__ BIO_B64_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int B64_BLOCK_SIZE ; 
 scalar_t__ B64_ENCODE ; 
 int BIO_FLAGS_BASE64_NO_NL ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_data (int /*<<< orphan*/ *) ; 
 int BIO_get_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int BIO_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* EVP_EncodeBlock (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  EVP_EncodeInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_EncodeUpdate (int /*<<< orphan*/ ,unsigned char*,int*,unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static int b64_write(BIO *b, const char *in, int inl)
{
    int ret = 0;
    int n;
    int i;
    BIO_B64_CTX *ctx;
    BIO *next;

    ctx = (BIO_B64_CTX *)BIO_get_data(b);
    next = BIO_next(b);
    if ((ctx == NULL) || (next == NULL))
        return 0;

    BIO_clear_retry_flags(b);

    if (ctx->encode != B64_ENCODE) {
        ctx->encode = B64_ENCODE;
        ctx->buf_len = 0;
        ctx->buf_off = 0;
        ctx->tmp_len = 0;
        EVP_EncodeInit(ctx->base64);
    }

    OPENSSL_assert(ctx->buf_off < (int)sizeof(ctx->buf));
    OPENSSL_assert(ctx->buf_len <= (int)sizeof(ctx->buf));
    OPENSSL_assert(ctx->buf_len >= ctx->buf_off);
    n = ctx->buf_len - ctx->buf_off;
    while (n > 0) {
        i = BIO_write(next, &(ctx->buf[ctx->buf_off]), n);
        if (i <= 0) {
            BIO_copy_next_retry(b);
            return i;
        }
        OPENSSL_assert(i <= n);
        ctx->buf_off += i;
        OPENSSL_assert(ctx->buf_off <= (int)sizeof(ctx->buf));
        OPENSSL_assert(ctx->buf_len >= ctx->buf_off);
        n -= i;
    }
    /* at this point all pending data has been written */
    ctx->buf_off = 0;
    ctx->buf_len = 0;

    if ((in == NULL) || (inl <= 0))
        return 0;

    while (inl > 0) {
        n = (inl > B64_BLOCK_SIZE) ? B64_BLOCK_SIZE : inl;

        if (BIO_get_flags(b) & BIO_FLAGS_BASE64_NO_NL) {
            if (ctx->tmp_len > 0) {
                OPENSSL_assert(ctx->tmp_len <= 3);
                n = 3 - ctx->tmp_len;
                /*
                 * There's a theoretical possibility for this
                 */
                if (n > inl)
                    n = inl;
                memcpy(&(ctx->tmp[ctx->tmp_len]), in, n);
                ctx->tmp_len += n;
                ret += n;
                if (ctx->tmp_len < 3)
                    break;
                ctx->buf_len =
                    EVP_EncodeBlock((unsigned char *)ctx->buf,
                                    (unsigned char *)ctx->tmp, ctx->tmp_len);
                OPENSSL_assert(ctx->buf_len <= (int)sizeof(ctx->buf));
                OPENSSL_assert(ctx->buf_len >= ctx->buf_off);
                /*
                 * Since we're now done using the temporary buffer, the
                 * length should be 0'd
                 */
                ctx->tmp_len = 0;
            } else {
                if (n < 3) {
                    memcpy(ctx->tmp, in, n);
                    ctx->tmp_len = n;
                    ret += n;
                    break;
                }
                n -= n % 3;
                ctx->buf_len =
                    EVP_EncodeBlock((unsigned char *)ctx->buf,
                                    (const unsigned char *)in, n);
                OPENSSL_assert(ctx->buf_len <= (int)sizeof(ctx->buf));
                OPENSSL_assert(ctx->buf_len >= ctx->buf_off);
                ret += n;
            }
        } else {
            if (!EVP_EncodeUpdate(ctx->base64,
                                 (unsigned char *)ctx->buf, &ctx->buf_len,
                                 (unsigned char *)in, n))
                return ((ret == 0) ? -1 : ret);
            OPENSSL_assert(ctx->buf_len <= (int)sizeof(ctx->buf));
            OPENSSL_assert(ctx->buf_len >= ctx->buf_off);
            ret += n;
        }
        inl -= n;
        in += n;

        ctx->buf_off = 0;
        n = ctx->buf_len;
        while (n > 0) {
            i = BIO_write(next, &(ctx->buf[ctx->buf_off]), n);
            if (i <= 0) {
                BIO_copy_next_retry(b);
                return ((ret == 0) ? i : ret);
            }
            OPENSSL_assert(i <= n);
            n -= i;
            ctx->buf_off += i;
            OPENSSL_assert(ctx->buf_off <= (int)sizeof(ctx->buf));
            OPENSSL_assert(ctx->buf_len >= ctx->buf_off);
        }
        ctx->buf_len = 0;
        ctx->buf_off = 0;
    }
    return ret;
}