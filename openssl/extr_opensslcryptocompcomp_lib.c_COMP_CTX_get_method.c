#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  const* meth; } ;
typedef  int /*<<< orphan*/  COMP_METHOD ;
typedef  TYPE_1__ COMP_CTX ;

/* Variables and functions */

const COMP_METHOD *COMP_CTX_get_method(const COMP_CTX *ctx)
{
    return ctx->meth;
}