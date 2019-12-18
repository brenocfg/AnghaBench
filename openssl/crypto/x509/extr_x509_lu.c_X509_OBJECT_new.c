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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ X509_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  X509_F_X509_OBJECT_NEW ; 
 int /*<<< orphan*/  X509_LU_NONE ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

X509_OBJECT *X509_OBJECT_new(void)
{
    X509_OBJECT *ret = OPENSSL_zalloc(sizeof(*ret));

    if (ret == NULL) {
        X509err(X509_F_X509_OBJECT_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ret->type = X509_LU_NONE;
    return ret;
}