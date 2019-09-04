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
struct TYPE_5__ {int /*<<< orphan*/ * blob; } ;
struct TYPE_6__ {TYPE_1__ embedded; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ _; } ;
typedef  TYPE_3__ OSSL_STORE_INFO ;
typedef  int /*<<< orphan*/  BUF_MEM ;

/* Variables and functions */
 scalar_t__ OSSL_STORE_INFO_EMBEDDED ; 

BUF_MEM *ossl_store_info_get0_EMBEDDED_buffer(OSSL_STORE_INFO *info)
{
    if (info->type == OSSL_STORE_INFO_EMBEDDED)
        return info->_.embedded.blob;
    return NULL;
}