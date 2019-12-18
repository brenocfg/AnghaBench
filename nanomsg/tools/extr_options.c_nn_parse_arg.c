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
struct nn_parse_context {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_error_unexpected_argument (struct nn_parse_context*) ; 
 int /*<<< orphan*/  nn_parse_long_option (struct nn_parse_context*) ; 
 int /*<<< orphan*/  nn_parse_short_option (struct nn_parse_context*) ; 

__attribute__((used)) static void nn_parse_arg (struct nn_parse_context *ctx)
{
    if (ctx->data[0] == '-') {  /* an option */
        if (ctx->data[1] == '-') {  /* long option */
            if (ctx->data[2] == 0) {  /* end of options */
                return;
            }
            nn_parse_long_option (ctx);
        } else {
            ctx->data += 1;  /* Skip minus */
            while (*ctx->data) {
                nn_parse_short_option (ctx);
            }
        }
    } else {
        nn_error_unexpected_argument (ctx);
    }
}