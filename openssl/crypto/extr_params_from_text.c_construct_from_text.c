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
struct TYPE_4__ {int data_type; size_t data_size; scalar_t__ return_size; void* data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2nativepad (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  BN_is_negative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_hexstr2buf_ex (void*,size_t,size_t*,char const*) ; 
#define  OSSL_PARAM_INTEGER 131 
#define  OSSL_PARAM_OCTET_STRING 130 
#define  OSSL_PARAM_UNSIGNED_INTEGER 129 
#define  OSSL_PARAM_UTF8_STRING 128 
 int /*<<< orphan*/  memcpy (void*,char const*,size_t) ; 
 int /*<<< orphan*/  strncpy (void*,char const*,size_t) ; 

__attribute__((used)) static int construct_from_text(OSSL_PARAM *to, const OSSL_PARAM *paramdef,
                               const char *value, size_t value_n, int ishex,
                               void *buf, size_t buf_n, BIGNUM *tmpbn)
{
    if (buf == NULL)
        return 0;

    if (buf_n > 0) {
        switch (paramdef->data_type) {
        case OSSL_PARAM_INTEGER:
        case OSSL_PARAM_UNSIGNED_INTEGER:
            /*
            {
                if ((new_value = OPENSSL_malloc(new_value_n)) == NULL) {
                    BN_free(a);
                    break;
                }
            */

            BN_bn2nativepad(tmpbn, buf, buf_n);

            /*
             * 2s complement negate, part two.
             *
             * Because we did the first part on the BIGNUM itself, we can just
             * invert all the bytes here and be done with it.
             */
            if (paramdef->data_type == OSSL_PARAM_INTEGER
                && BN_is_negative(tmpbn)) {
                unsigned char *cp;
                size_t i = buf_n;

                for (cp = buf; i-- > 0; cp++)
                    *cp ^= 0xFF;
            }
            break;
        case OSSL_PARAM_UTF8_STRING:
            strncpy(buf, value, buf_n);
            break;
        case OSSL_PARAM_OCTET_STRING:
            if (ishex) {
                size_t l = 0;

                if (!OPENSSL_hexstr2buf_ex(buf, buf_n, &l, value))
                    return 0;
            } else {
                memcpy(buf, value, buf_n);
            }
            break;
        }
    }

    *to = *paramdef;
    to->data = buf;
    to->data_size = buf_n;
    to->return_size = 0;

    return 1;
}