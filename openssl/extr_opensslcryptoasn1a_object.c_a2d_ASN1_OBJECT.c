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
typedef  int /*<<< orphan*/  ftmp ;
typedef  scalar_t__ BN_ULONG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_A2D_ASN1_OBJECT ; 
 int /*<<< orphan*/  ASN1_R_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  ASN1_R_FIRST_NUM_TOO_LARGE ; 
 int /*<<< orphan*/  ASN1_R_INVALID_DIGIT ; 
 int /*<<< orphan*/  ASN1_R_INVALID_SEPARATOR ; 
 int /*<<< orphan*/  ASN1_R_MISSING_SECOND_NUMBER ; 
 int /*<<< orphan*/  ASN1_R_SECOND_NUMBER_TOO_LARGE ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,int) ; 
 scalar_t__ BN_div_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul_word (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (int) ; 
 int ULONG_MAX ; 
 int /*<<< orphan*/  ossl_isdigit (int) ; 
 int strlen (char const*) ; 

int a2d_ASN1_OBJECT(unsigned char *out, int olen, const char *buf, int num)
{
    int i, first, len = 0, c, use_bn;
    char ftmp[24], *tmp = ftmp;
    int tmpsize = sizeof(ftmp);
    const char *p;
    unsigned long l;
    BIGNUM *bl = NULL;

    if (num == 0)
        return 0;
    else if (num == -1)
        num = strlen(buf);

    p = buf;
    c = *(p++);
    num--;
    if ((c >= '0') && (c <= '2')) {
        first = c - '0';
    } else {
        ASN1err(ASN1_F_A2D_ASN1_OBJECT, ASN1_R_FIRST_NUM_TOO_LARGE);
        goto err;
    }

    if (num <= 0) {
        ASN1err(ASN1_F_A2D_ASN1_OBJECT, ASN1_R_MISSING_SECOND_NUMBER);
        goto err;
    }
    c = *(p++);
    num--;
    for (;;) {
        if (num <= 0)
            break;
        if ((c != '.') && (c != ' ')) {
            ASN1err(ASN1_F_A2D_ASN1_OBJECT, ASN1_R_INVALID_SEPARATOR);
            goto err;
        }
        l = 0;
        use_bn = 0;
        for (;;) {
            if (num <= 0)
                break;
            num--;
            c = *(p++);
            if ((c == ' ') || (c == '.'))
                break;
            if (!ossl_isdigit(c)) {
                ASN1err(ASN1_F_A2D_ASN1_OBJECT, ASN1_R_INVALID_DIGIT);
                goto err;
            }
            if (!use_bn && l >= ((ULONG_MAX - 80) / 10L)) {
                use_bn = 1;
                if (bl == NULL)
                    bl = BN_new();
                if (bl == NULL || !BN_set_word(bl, l))
                    goto err;
            }
            if (use_bn) {
                if (!BN_mul_word(bl, 10L)
                    || !BN_add_word(bl, c - '0'))
                    goto err;
            } else
                l = l * 10L + (long)(c - '0');
        }
        if (len == 0) {
            if ((first < 2) && (l >= 40)) {
                ASN1err(ASN1_F_A2D_ASN1_OBJECT,
                        ASN1_R_SECOND_NUMBER_TOO_LARGE);
                goto err;
            }
            if (use_bn) {
                if (!BN_add_word(bl, first * 40))
                    goto err;
            } else
                l += (long)first *40;
        }
        i = 0;
        if (use_bn) {
            int blsize;
            blsize = BN_num_bits(bl);
            blsize = (blsize + 6) / 7;
            if (blsize > tmpsize) {
                if (tmp != ftmp)
                    OPENSSL_free(tmp);
                tmpsize = blsize + 32;
                tmp = OPENSSL_malloc(tmpsize);
                if (tmp == NULL)
                    goto err;
            }
            while (blsize--) {
                BN_ULONG t = BN_div_word(bl, 0x80L);
                if (t == (BN_ULONG)-1)
                    goto err;
                tmp[i++] = (unsigned char)t;
            }
        } else {

            for (;;) {
                tmp[i++] = (unsigned char)l & 0x7f;
                l >>= 7L;
                if (l == 0L)
                    break;
            }

        }
        if (out != NULL) {
            if (len + i > olen) {
                ASN1err(ASN1_F_A2D_ASN1_OBJECT, ASN1_R_BUFFER_TOO_SMALL);
                goto err;
            }
            while (--i > 0)
                out[len++] = tmp[i] | 0x80;
            out[len++] = tmp[0];
        } else
            len += i;
    }
    if (tmp != ftmp)
        OPENSSL_free(tmp);
    BN_free(bl);
    return len;
 err:
    if (tmp != ftmp)
        OPENSSL_free(tmp);
    BN_free(bl);
    return 0;
}