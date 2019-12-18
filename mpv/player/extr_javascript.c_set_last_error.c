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
struct script_ctx {scalar_t__* last_error_str; } ;

/* Variables and functions */
 scalar_t__* talloc_strdup_append (scalar_t__*,char const*) ; 

__attribute__((used)) static void set_last_error(struct script_ctx *ctx, bool iserr, const char *str)
{
    ctx->last_error_str[0] = 0;
    if (!iserr)
        return;
    if (!str || !str[0])
        str = "Error";
    ctx->last_error_str = talloc_strdup_append(ctx->last_error_str, str);
}