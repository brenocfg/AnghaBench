#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  functions; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 TYPE_1__ hlsl_ctx ; 
 int /*<<< orphan*/ * wine_rb_get (int /*<<< orphan*/ *,char const*) ; 

BOOL find_function(const char *name)
{
    return wine_rb_get(&hlsl_ctx.functions, name) != NULL;
}