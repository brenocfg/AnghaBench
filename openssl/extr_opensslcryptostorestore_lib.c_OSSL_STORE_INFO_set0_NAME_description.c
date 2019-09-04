#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* desc; } ;
struct TYPE_6__ {TYPE_1__ name; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ _; } ;
typedef  TYPE_3__ OSSL_STORE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_PASSED_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  OSSL_STORE_F_OSSL_STORE_INFO_SET0_NAME_DESCRIPTION ; 
 scalar_t__ OSSL_STORE_INFO_NAME ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int OSSL_STORE_INFO_set0_NAME_description(OSSL_STORE_INFO *info, char *desc)
{
    if (info->type != OSSL_STORE_INFO_NAME) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_INFO_SET0_NAME_DESCRIPTION,
                      ERR_R_PASSED_INVALID_ARGUMENT);
        return 0;
    }

    info->_.name.desc = desc;

    return 1;
}