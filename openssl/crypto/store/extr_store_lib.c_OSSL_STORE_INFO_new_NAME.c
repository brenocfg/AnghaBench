#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; int /*<<< orphan*/ * desc; } ;
struct TYPE_7__ {TYPE_1__ name; } ;
struct TYPE_8__ {TYPE_2__ _; } ;
typedef  TYPE_3__ OSSL_STORE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OSSL_STORE_F_OSSL_STORE_INFO_NEW_NAME ; 
 int /*<<< orphan*/  OSSL_STORE_INFO_NAME ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* store_info_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

OSSL_STORE_INFO *OSSL_STORE_INFO_new_NAME(char *name)
{
    OSSL_STORE_INFO *info = store_info_new(OSSL_STORE_INFO_NAME, NULL);

    if (info == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_INFO_NEW_NAME,
                      ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    info->_.name.name = name;
    info->_.name.desc = NULL;

    return info;
}