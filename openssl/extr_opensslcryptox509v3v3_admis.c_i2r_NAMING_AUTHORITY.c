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
struct v3_ext_method {int dummy; } ;
typedef  int /*<<< orphan*/  objbuf ;
struct TYPE_2__ {int /*<<< orphan*/ * namingAuthorityUrl; int /*<<< orphan*/ * namingAuthorityText; int /*<<< orphan*/ * namingAuthorityId; } ;
typedef  TYPE_1__ NAMING_AUTHORITY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ ASN1_STRING_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 char* OBJ_nid2ln (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_obj2nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_obj2txt (char*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int i2r_NAMING_AUTHORITY(const struct v3_ext_method *method, void *in,
                                BIO *bp, int ind)
{
    NAMING_AUTHORITY * namingAuthority = (NAMING_AUTHORITY*) in;

    if (namingAuthority == NULL)
        return 0;

    if (namingAuthority->namingAuthorityId == NULL
        && namingAuthority->namingAuthorityText == NULL
        && namingAuthority->namingAuthorityUrl == NULL)
        return 0;

    if (BIO_printf(bp, "%*snamingAuthority: ", ind, "") <= 0)
        goto err;

    if (namingAuthority->namingAuthorityId != NULL) {
        char objbuf[128];
        const char *ln = OBJ_nid2ln(OBJ_obj2nid(namingAuthority->namingAuthorityId));

        if (BIO_printf(bp, "%*s  admissionAuthorityId: ", ind, "") <= 0)
            goto err;

        OBJ_obj2txt(objbuf, sizeof(objbuf), namingAuthority->namingAuthorityId, 1);

        if (BIO_printf(bp, "%s%s%s%s\n", ln ? ln : "",
                       ln ? " (" : "", objbuf, ln ? ")" : "") <= 0)
            goto err;
    }
    if (namingAuthority->namingAuthorityText != NULL) {
        if (BIO_printf(bp, "%*s  namingAuthorityText: ", ind, "") <= 0
            || ASN1_STRING_print(bp, namingAuthority->namingAuthorityText) <= 0
            || BIO_printf(bp, "\n") <= 0)
            goto err;
    }
    if (namingAuthority->namingAuthorityUrl != NULL ) {
        if (BIO_printf(bp, "%*s  namingAuthorityUrl: ", ind, "") <= 0
            || ASN1_STRING_print(bp, namingAuthority->namingAuthorityUrl) <= 0
            || BIO_printf(bp, "\n") <= 0)
            goto err;
    }
    return 1;

err:
    return 0;
}