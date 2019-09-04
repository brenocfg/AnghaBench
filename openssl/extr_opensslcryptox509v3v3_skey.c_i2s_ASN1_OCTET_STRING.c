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
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ASN1_OCTET_STRING ;

/* Variables and functions */
 char* OPENSSL_buf2hexstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *i2s_ASN1_OCTET_STRING(X509V3_EXT_METHOD *method,
                            const ASN1_OCTET_STRING *oct)
{
    return OPENSSL_buf2hexstr(oct->data, oct->length);
}