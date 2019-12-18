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
struct TYPE_3__ {int data_type; int key; int data_size; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 int BIO_snprintf (char*,size_t,char*,...) ; 
#define  OSSL_PARAM_INTEGER 133 
#define  OSSL_PARAM_OCTET_PTR 132 
#define  OSSL_PARAM_OCTET_STRING 131 
#define  OSSL_PARAM_UNSIGNED_INTEGER 130 
#define  OSSL_PARAM_UTF8_PTR 129 
#define  OSSL_PARAM_UTF8_STRING 128 

__attribute__((used)) static int describe_param_type(char *buf, size_t bufsz, const OSSL_PARAM *param)
{
    const char *type_mod = "";
    const char *type = NULL;
    int show_type_number = 0;
    int printed_len;

    switch (param->data_type) {
    case OSSL_PARAM_UNSIGNED_INTEGER:
        type_mod = "unsigned ";
        /* FALLTHRU */
    case OSSL_PARAM_INTEGER:
        type = "integer";
        break;
    case OSSL_PARAM_UTF8_PTR:
        type_mod = "pointer to a ";
        /* FALLTHRU */
    case OSSL_PARAM_UTF8_STRING:
        type = "UTF8 encoded string";
        break;
    case OSSL_PARAM_OCTET_PTR:
        type_mod = "pointer to an ";
        /* FALLTHRU */
    case OSSL_PARAM_OCTET_STRING:
        type = "octet string";
        break;
    default:
        type = "unknown type";
        show_type_number = 1;
        break;
    }

    printed_len = BIO_snprintf(buf, bufsz, "%s: ", param->key);
    if (printed_len > 0) {
        buf += printed_len;
        bufsz -= printed_len;
    }
    printed_len = BIO_snprintf(buf, bufsz, "%s%s", type_mod, type);
    if (printed_len > 0) {
        buf += printed_len;
        bufsz -= printed_len;
    }
    if (show_type_number) {
        printed_len = BIO_snprintf(buf, bufsz, " [%d]", param->data_type);
        if (printed_len > 0) {
            buf += printed_len;
            bufsz -= printed_len;
        }
    }
    if (param->data_size == 0)
        printed_len = BIO_snprintf(buf, bufsz, " (arbitrary size)");
    else
        printed_len = BIO_snprintf(buf, bufsz, " (max %zu bytes large)",
                                   param->data_size);
    if (printed_len > 0) {
        buf += printed_len;
        bufsz -= printed_len;
    }
    *buf = '\0';
    return 1;
}