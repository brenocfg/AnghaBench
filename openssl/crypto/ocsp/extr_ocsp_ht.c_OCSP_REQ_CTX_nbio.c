#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; unsigned char const* iobuf; int iobuflen; int asn1_len; int max_resp_len; int /*<<< orphan*/  mem; int /*<<< orphan*/  io; } ;
typedef  TYPE_1__ OCSP_REQ_CTX ;

/* Variables and functions */
 int BIO_flush (int /*<<< orphan*/ ) ; 
 void* BIO_get_mem_data (int /*<<< orphan*/ ,unsigned char const**) ; 
 int BIO_gets (int /*<<< orphan*/ ,char*,int) ; 
 int BIO_read (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  BIO_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_should_retry (int /*<<< orphan*/ ) ; 
 int BIO_write (int /*<<< orphan*/ ,...) ; 
#define  OHS_ASN1_CONTENT 137 
#define  OHS_ASN1_FLUSH 136 
#define  OHS_ASN1_HEADER 135 
#define  OHS_ASN1_WRITE 134 
#define  OHS_ASN1_WRITE_INIT 133 
#define  OHS_DONE 132 
#define  OHS_ERROR 131 
#define  OHS_FIRSTLINE 130 
#define  OHS_HEADERS 129 
#define  OHS_HTTP_HEADER 128 
 int OHS_NOREAD ; 
 int V_ASN1_CONSTRUCTED ; 
 int V_ASN1_SEQUENCE ; 
 int /*<<< orphan*/  memchr (unsigned char const*,char,int) ; 
 int /*<<< orphan*/  parse_http_line1 (char*) ; 

int OCSP_REQ_CTX_nbio(OCSP_REQ_CTX *rctx)
{
    int i, n;
    const unsigned char *p;
 next_io:
    if (!(rctx->state & OHS_NOREAD)) {
        n = BIO_read(rctx->io, rctx->iobuf, rctx->iobuflen);

        if (n <= 0) {
            if (BIO_should_retry(rctx->io))
                return -1;
            return 0;
        }

        /* Write data to memory BIO */

        if (BIO_write(rctx->mem, rctx->iobuf, n) != n)
            return 0;
    }

    switch (rctx->state) {
    case OHS_HTTP_HEADER:
        /* Last operation was adding headers: need a final \r\n */
        if (BIO_write(rctx->mem, "\r\n", 2) != 2) {
            rctx->state = OHS_ERROR;
            return 0;
        }
        rctx->state = OHS_ASN1_WRITE_INIT;

        /* fall thru */
    case OHS_ASN1_WRITE_INIT:
        rctx->asn1_len = BIO_get_mem_data(rctx->mem, NULL);
        rctx->state = OHS_ASN1_WRITE;

        /* fall thru */
    case OHS_ASN1_WRITE:
        n = BIO_get_mem_data(rctx->mem, &p);

        i = BIO_write(rctx->io, p + (n - rctx->asn1_len), rctx->asn1_len);

        if (i <= 0) {
            if (BIO_should_retry(rctx->io))
                return -1;
            rctx->state = OHS_ERROR;
            return 0;
        }

        rctx->asn1_len -= i;

        if (rctx->asn1_len > 0)
            goto next_io;

        rctx->state = OHS_ASN1_FLUSH;

        (void)BIO_reset(rctx->mem);

        /* fall thru */
    case OHS_ASN1_FLUSH:

        i = BIO_flush(rctx->io);

        if (i > 0) {
            rctx->state = OHS_FIRSTLINE;
            goto next_io;
        }

        if (BIO_should_retry(rctx->io))
            return -1;

        rctx->state = OHS_ERROR;
        return 0;

    case OHS_ERROR:
        return 0;

    case OHS_FIRSTLINE:
    case OHS_HEADERS:

        /* Attempt to read a line in */

 next_line:
        /*
         * Due to &%^*$" memory BIO behaviour with BIO_gets we have to check
         * there's a complete line in there before calling BIO_gets or we'll
         * just get a partial read.
         */
        n = BIO_get_mem_data(rctx->mem, &p);
        if ((n <= 0) || !memchr(p, '\n', n)) {
            if (n >= rctx->iobuflen) {
                rctx->state = OHS_ERROR;
                return 0;
            }
            goto next_io;
        }
        n = BIO_gets(rctx->mem, (char *)rctx->iobuf, rctx->iobuflen);

        if (n <= 0) {
            if (BIO_should_retry(rctx->mem))
                goto next_io;
            rctx->state = OHS_ERROR;
            return 0;
        }

        /* Don't allow excessive lines */
        if (n == rctx->iobuflen) {
            rctx->state = OHS_ERROR;
            return 0;
        }

        /* First line */
        if (rctx->state == OHS_FIRSTLINE) {
            if (parse_http_line1((char *)rctx->iobuf)) {
                rctx->state = OHS_HEADERS;
                goto next_line;
            } else {
                rctx->state = OHS_ERROR;
                return 0;
            }
        } else {
            /* Look for blank line: end of headers */
            for (p = rctx->iobuf; *p; p++) {
                if ((*p != '\r') && (*p != '\n'))
                    break;
            }
            if (*p)
                goto next_line;

            rctx->state = OHS_ASN1_HEADER;

        }

        /* Fall thru */

    case OHS_ASN1_HEADER:
        /*
         * Now reading ASN1 header: can read at least 2 bytes which is enough
         * for ASN1 SEQUENCE header and either length field or at least the
         * length of the length field.
         */
        n = BIO_get_mem_data(rctx->mem, &p);
        if (n < 2)
            goto next_io;

        /* Check it is an ASN1 SEQUENCE */
        if (*p++ != (V_ASN1_SEQUENCE | V_ASN1_CONSTRUCTED)) {
            rctx->state = OHS_ERROR;
            return 0;
        }

        /* Check out length field */
        if (*p & 0x80) {
            /*
             * If MSB set on initial length octet we can now always read 6
             * octets: make sure we have them.
             */
            if (n < 6)
                goto next_io;
            n = *p & 0x7F;
            /* Not NDEF or excessive length */
            if (!n || (n > 4)) {
                rctx->state = OHS_ERROR;
                return 0;
            }
            p++;
            rctx->asn1_len = 0;
            for (i = 0; i < n; i++) {
                rctx->asn1_len <<= 8;
                rctx->asn1_len |= *p++;
            }

            if (rctx->asn1_len > rctx->max_resp_len) {
                rctx->state = OHS_ERROR;
                return 0;
            }

            rctx->asn1_len += n + 2;
        } else
            rctx->asn1_len = *p + 2;

        rctx->state = OHS_ASN1_CONTENT;

        /* Fall thru */

    case OHS_ASN1_CONTENT:
        n = BIO_get_mem_data(rctx->mem, NULL);
        if (n < (int)rctx->asn1_len)
            goto next_io;

        rctx->state = OHS_DONE;
        return 1;

    case OHS_DONE:
        return 1;

    }

    return 0;

}