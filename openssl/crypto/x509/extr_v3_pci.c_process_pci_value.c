#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_10__ {unsigned char* data; long length; } ;
struct TYPE_9__ {unsigned char* value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ CONF_VALUE ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_2__ ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (TYPE_2__*) ; 
 TYPE_2__* ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (unsigned char*,char*) ; 
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ BIO_should_retry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_BIO_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OBJ_txt2obj (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_hexstr2buf (unsigned char*,long*) ; 
 unsigned char* OPENSSL_realloc (unsigned char*,long) ; 
 int /*<<< orphan*/  X509V3_F_PROCESS_PCI_VALUE ; 
 int /*<<< orphan*/  X509V3_R_INCORRECT_POLICY_SYNTAX_TAG ; 
 int /*<<< orphan*/  X509V3_R_INVALID_OBJECT_IDENTIFIER ; 
 int /*<<< orphan*/  X509V3_R_POLICY_LANGUAGE_ALREADY_DEFINED ; 
 int /*<<< orphan*/  X509V3_R_POLICY_PATH_LENGTH ; 
 int /*<<< orphan*/  X509V3_R_POLICY_PATH_LENGTH_ALREADY_DEFINED ; 
 int /*<<< orphan*/  X509V3_conf_err (TYPE_1__*) ; 
 int /*<<< orphan*/  X509V3_get_value_int (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,long) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 long strlen (unsigned char*) ; 
 scalar_t__ strncmp (unsigned char*,char*,int) ; 

__attribute__((used)) static int process_pci_value(CONF_VALUE *val,
                             ASN1_OBJECT **language, ASN1_INTEGER **pathlen,
                             ASN1_OCTET_STRING **policy)
{
    int free_policy = 0;

    if (strcmp(val->name, "language") == 0) {
        if (*language) {
            X509V3err(X509V3_F_PROCESS_PCI_VALUE,
                      X509V3_R_POLICY_LANGUAGE_ALREADY_DEFINED);
            X509V3_conf_err(val);
            return 0;
        }
        if ((*language = OBJ_txt2obj(val->value, 0)) == NULL) {
            X509V3err(X509V3_F_PROCESS_PCI_VALUE,
                      X509V3_R_INVALID_OBJECT_IDENTIFIER);
            X509V3_conf_err(val);
            return 0;
        }
    } else if (strcmp(val->name, "pathlen") == 0) {
        if (*pathlen) {
            X509V3err(X509V3_F_PROCESS_PCI_VALUE,
                      X509V3_R_POLICY_PATH_LENGTH_ALREADY_DEFINED);
            X509V3_conf_err(val);
            return 0;
        }
        if (!X509V3_get_value_int(val, pathlen)) {
            X509V3err(X509V3_F_PROCESS_PCI_VALUE,
                      X509V3_R_POLICY_PATH_LENGTH);
            X509V3_conf_err(val);
            return 0;
        }
    } else if (strcmp(val->name, "policy") == 0) {
        unsigned char *tmp_data = NULL;
        long val_len;

        if (*policy == NULL) {
            *policy = ASN1_OCTET_STRING_new();
            if (*policy == NULL) {
                X509V3err(X509V3_F_PROCESS_PCI_VALUE, ERR_R_MALLOC_FAILURE);
                X509V3_conf_err(val);
                return 0;
            }
            free_policy = 1;
        }
        if (strncmp(val->value, "hex:", 4) == 0) {
            unsigned char *tmp_data2 =
                OPENSSL_hexstr2buf(val->value + 4, &val_len);

            if (!tmp_data2) {
                X509V3_conf_err(val);
                goto err;
            }

            tmp_data = OPENSSL_realloc((*policy)->data,
                                       (*policy)->length + val_len + 1);
            if (tmp_data) {
                (*policy)->data = tmp_data;
                memcpy(&(*policy)->data[(*policy)->length],
                       tmp_data2, val_len);
                (*policy)->length += val_len;
                (*policy)->data[(*policy)->length] = '\0';
            } else {
                OPENSSL_free(tmp_data2);
                /*
                 * realloc failure implies the original data space is b0rked
                 * too!
                 */
                OPENSSL_free((*policy)->data);
                (*policy)->data = NULL;
                (*policy)->length = 0;
                X509V3err(X509V3_F_PROCESS_PCI_VALUE, ERR_R_MALLOC_FAILURE);
                X509V3_conf_err(val);
                goto err;
            }
            OPENSSL_free(tmp_data2);
        } else if (strncmp(val->value, "file:", 5) == 0) {
            unsigned char buf[2048];
            int n;
            BIO *b = BIO_new_file(val->value + 5, "r");
            if (!b) {
                X509V3err(X509V3_F_PROCESS_PCI_VALUE, ERR_R_BIO_LIB);
                X509V3_conf_err(val);
                goto err;
            }
            while ((n = BIO_read(b, buf, sizeof(buf))) > 0
                   || (n == 0 && BIO_should_retry(b))) {
                if (!n)
                    continue;

                tmp_data = OPENSSL_realloc((*policy)->data,
                                           (*policy)->length + n + 1);

                if (!tmp_data) {
                    OPENSSL_free((*policy)->data);
                    (*policy)->data = NULL;
                    (*policy)->length = 0;
                    X509V3err(X509V3_F_PROCESS_PCI_VALUE,
                              ERR_R_MALLOC_FAILURE);
                    X509V3_conf_err(val);
                    BIO_free_all(b);
                    goto err;
                }

                (*policy)->data = tmp_data;
                memcpy(&(*policy)->data[(*policy)->length], buf, n);
                (*policy)->length += n;
                (*policy)->data[(*policy)->length] = '\0';
            }
            BIO_free_all(b);

            if (n < 0) {
                X509V3err(X509V3_F_PROCESS_PCI_VALUE, ERR_R_BIO_LIB);
                X509V3_conf_err(val);
                goto err;
            }
        } else if (strncmp(val->value, "text:", 5) == 0) {
            val_len = strlen(val->value + 5);
            tmp_data = OPENSSL_realloc((*policy)->data,
                                       (*policy)->length + val_len + 1);
            if (tmp_data) {
                (*policy)->data = tmp_data;
                memcpy(&(*policy)->data[(*policy)->length],
                       val->value + 5, val_len);
                (*policy)->length += val_len;
                (*policy)->data[(*policy)->length] = '\0';
            } else {
                /*
                 * realloc failure implies the original data space is b0rked
                 * too!
                 */
                OPENSSL_free((*policy)->data);
                (*policy)->data = NULL;
                (*policy)->length = 0;
                X509V3err(X509V3_F_PROCESS_PCI_VALUE, ERR_R_MALLOC_FAILURE);
                X509V3_conf_err(val);
                goto err;
            }
        } else {
            X509V3err(X509V3_F_PROCESS_PCI_VALUE,
                      X509V3_R_INCORRECT_POLICY_SYNTAX_TAG);
            X509V3_conf_err(val);
            goto err;
        }
        if (!tmp_data) {
            X509V3err(X509V3_F_PROCESS_PCI_VALUE, ERR_R_MALLOC_FAILURE);
            X509V3_conf_err(val);
            goto err;
        }
    }
    return 1;
 err:
    if (free_policy) {
        ASN1_OCTET_STRING_free(*policy);
        *policy = NULL;
    }
    return 0;
}