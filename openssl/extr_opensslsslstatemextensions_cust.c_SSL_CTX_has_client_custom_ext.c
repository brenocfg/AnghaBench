#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* cert; } ;
struct TYPE_4__ {int /*<<< orphan*/  custext; } ;
typedef  TYPE_2__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ENDPOINT_CLIENT ; 
 int /*<<< orphan*/ * custom_ext_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 

int SSL_CTX_has_client_custom_ext(const SSL_CTX *ctx, unsigned int ext_type)
{
    return custom_ext_find(&ctx->cert->custext, ENDPOINT_CLIENT, ext_type,
                           NULL) != NULL;
}