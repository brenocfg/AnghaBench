#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tbuf ;
struct TYPE_4__ {unsigned char* data; int length; } ;
typedef  int /*<<< orphan*/  BIGNUM ;
typedef  TYPE_1__ ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,unsigned char) ; 
 char* BN_bn2dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_lshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  BN_sub_word (int /*<<< orphan*/ *,int) ; 
 scalar_t__ DECIMAL_SIZE (unsigned long) ; 
 int NID_undef ; 
 char* OBJ_nid2ln (int) ; 
 char* OBJ_nid2sn (int) ; 
 int OBJ_obj2nid (TYPE_1__ const*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char const*,int) ; 
 long ULONG_MAX ; 
 int strlen (char const*) ; 

int OBJ_obj2txt(char *buf, int buf_len, const ASN1_OBJECT *a, int no_name)
{
    int i, n = 0, len, nid, first, use_bn;
    BIGNUM *bl;
    unsigned long l;
    const unsigned char *p;
    char tbuf[DECIMAL_SIZE(i) + DECIMAL_SIZE(l) + 2];

    /* Ensure that, at every state, |buf| is NUL-terminated. */
    if (buf && buf_len > 0)
        buf[0] = '\0';

    if ((a == NULL) || (a->data == NULL))
        return 0;

    if (!no_name && (nid = OBJ_obj2nid(a)) != NID_undef) {
        const char *s;
        s = OBJ_nid2ln(nid);
        if (s == NULL)
            s = OBJ_nid2sn(nid);
        if (s) {
            if (buf)
                OPENSSL_strlcpy(buf, s, buf_len);
            n = strlen(s);
            return n;
        }
    }

    len = a->length;
    p = a->data;

    first = 1;
    bl = NULL;

    while (len > 0) {
        l = 0;
        use_bn = 0;
        for (;;) {
            unsigned char c = *p++;
            len--;
            if ((len == 0) && (c & 0x80))
                goto err;
            if (use_bn) {
                if (!BN_add_word(bl, c & 0x7f))
                    goto err;
            } else
                l |= c & 0x7f;
            if (!(c & 0x80))
                break;
            if (!use_bn && (l > (ULONG_MAX >> 7L))) {
                if (bl == NULL && (bl = BN_new()) == NULL)
                    goto err;
                if (!BN_set_word(bl, l))
                    goto err;
                use_bn = 1;
            }
            if (use_bn) {
                if (!BN_lshift(bl, bl, 7))
                    goto err;
            } else
                l <<= 7L;
        }

        if (first) {
            first = 0;
            if (l >= 80) {
                i = 2;
                if (use_bn) {
                    if (!BN_sub_word(bl, 80))
                        goto err;
                } else
                    l -= 80;
            } else {
                i = (int)(l / 40);
                l -= (long)(i * 40);
            }
            if (buf && (buf_len > 1)) {
                *buf++ = i + '0';
                *buf = '\0';
                buf_len--;
            }
            n++;
        }

        if (use_bn) {
            char *bndec;
            bndec = BN_bn2dec(bl);
            if (!bndec)
                goto err;
            i = strlen(bndec);
            if (buf) {
                if (buf_len > 1) {
                    *buf++ = '.';
                    *buf = '\0';
                    buf_len--;
                }
                OPENSSL_strlcpy(buf, bndec, buf_len);
                if (i > buf_len) {
                    buf += buf_len;
                    buf_len = 0;
                } else {
                    buf += i;
                    buf_len -= i;
                }
            }
            n++;
            n += i;
            OPENSSL_free(bndec);
        } else {
            BIO_snprintf(tbuf, sizeof(tbuf), ".%lu", l);
            i = strlen(tbuf);
            if (buf && (buf_len > 0)) {
                OPENSSL_strlcpy(buf, tbuf, buf_len);
                if (i > buf_len) {
                    buf += buf_len;
                    buf_len = 0;
                } else {
                    buf += i;
                    buf_len -= i;
                }
            }
            n += i;
            l = 0;
        }
    }

    BN_free(bl);
    return n;

 err:
    BN_free(bl);
    return -1;
}