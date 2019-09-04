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
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;
struct TYPE_3__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ASN1_IA5STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  X509V3_F_I2S_ASN1_IA5STRING ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

char *i2s_ASN1_IA5STRING(X509V3_EXT_METHOD *method, ASN1_IA5STRING *ia5)
{
    char *tmp;

    if (!ia5 || !ia5->length)
        return NULL;
    if ((tmp = OPENSSL_malloc(ia5->length + 1)) == NULL) {
        X509V3err(X509V3_F_I2S_ASN1_IA5STRING, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    memcpy(tmp, ia5->data, ia5->length);
    tmp[ia5->length] = 0;
    return tmp;
}