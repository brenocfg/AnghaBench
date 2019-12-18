#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;
struct TYPE_6__ {int /*<<< orphan*/  ids; int /*<<< orphan*/  version; } ;
struct TYPE_5__ {int /*<<< orphan*/  user; int /*<<< orphan*/  zone; } ;
typedef  TYPE_1__ SXNETID ;
typedef  TYPE_2__ SXNET ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 long ASN1_INTEGER_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_STRING_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int,char*,...) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* i2s_ASN1_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sk_SXNETID_num (int /*<<< orphan*/ ) ; 
 TYPE_1__* sk_SXNETID_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sxnet_i2r(X509V3_EXT_METHOD *method, SXNET *sx, BIO *out,
                     int indent)
{
    long v;
    char *tmp;
    SXNETID *id;
    int i;
    v = ASN1_INTEGER_get(sx->version);
    BIO_printf(out, "%*sVersion: %ld (0x%lX)", indent, "", v + 1, v);
    for (i = 0; i < sk_SXNETID_num(sx->ids); i++) {
        id = sk_SXNETID_value(sx->ids, i);
        tmp = i2s_ASN1_INTEGER(NULL, id->zone);
        BIO_printf(out, "\n%*sZone: %s, User: ", indent, "", tmp);
        OPENSSL_free(tmp);
        ASN1_STRING_print(out, id->user);
    }
    return 1;
}