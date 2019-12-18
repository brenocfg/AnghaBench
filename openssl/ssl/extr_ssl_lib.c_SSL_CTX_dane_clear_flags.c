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
struct TYPE_4__ {unsigned long flags; } ;
struct TYPE_5__ {TYPE_1__ dane; } ;
typedef  TYPE_2__ SSL_CTX ;

/* Variables and functions */

unsigned long SSL_CTX_dane_clear_flags(SSL_CTX *ctx, unsigned long flags)
{
    unsigned long orig = ctx->dane.flags;

    ctx->dane.flags &= ~flags;
    return orig;
}