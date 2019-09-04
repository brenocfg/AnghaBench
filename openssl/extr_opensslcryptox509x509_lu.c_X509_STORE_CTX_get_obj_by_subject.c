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
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509_OBJECT ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509_LOOKUP_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  X509_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_OBJECT_new () ; 
 int /*<<< orphan*/  X509_STORE_CTX_get_by_subject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

X509_OBJECT *X509_STORE_CTX_get_obj_by_subject(X509_STORE_CTX *vs,
                                               X509_LOOKUP_TYPE type,
                                               X509_NAME *name)
{
    X509_OBJECT *ret = X509_OBJECT_new();

    if (ret == NULL)
        return NULL;
    if (!X509_STORE_CTX_get_by_subject(vs, type, name, ret)) {
        X509_OBJECT_free(ret);
        return NULL;
    }
    return ret;
}