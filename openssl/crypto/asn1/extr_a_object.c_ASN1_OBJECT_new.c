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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_OBJECT_NEW ; 
 int /*<<< orphan*/  ASN1_OBJECT_FLAG_DYNAMIC ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

ASN1_OBJECT *ASN1_OBJECT_new(void)
{
    ASN1_OBJECT *ret;

    ret = OPENSSL_zalloc(sizeof(*ret));
    if (ret == NULL) {
        ASN1err(ASN1_F_ASN1_OBJECT_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ret->flags = ASN1_OBJECT_FLAG_DYNAMIC;
    return ret;
}