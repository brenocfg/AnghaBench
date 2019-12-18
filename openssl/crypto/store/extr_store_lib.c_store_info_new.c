#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* data; } ;
struct TYPE_6__ {int type; TYPE_1__ _; } ;
typedef  TYPE_2__ OSSL_STORE_INFO ;

/* Variables and functions */
 TYPE_2__* OPENSSL_zalloc (int) ; 

__attribute__((used)) static OSSL_STORE_INFO *store_info_new(int type, void *data)
{
    OSSL_STORE_INFO *info = OPENSSL_zalloc(sizeof(*info));

    if (info == NULL)
        return NULL;

    info->type = type;
    info->_.data = data;
    return info;
}