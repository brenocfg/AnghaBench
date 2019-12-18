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
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  X509V3_F_X509V3_EXT_ADD ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext_cmp ; 
 int /*<<< orphan*/ * ext_list ; 
 int /*<<< orphan*/ * sk_X509V3_EXT_METHOD_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509V3_EXT_METHOD_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int X509V3_EXT_add(X509V3_EXT_METHOD *ext)
{
    if (ext_list == NULL
        && (ext_list = sk_X509V3_EXT_METHOD_new(ext_cmp)) == NULL) {
        X509V3err(X509V3_F_X509V3_EXT_ADD, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    if (!sk_X509V3_EXT_METHOD_push(ext_list, ext)) {
        X509V3err(X509V3_F_X509V3_EXT_ADD, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    return 1;
}