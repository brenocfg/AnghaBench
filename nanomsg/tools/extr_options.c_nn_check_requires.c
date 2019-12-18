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
struct nn_parse_context {int mask; int requires; char** argv; int /*<<< orphan*/ * last_option_usage; struct nn_option* options; } ;
struct nn_option {int requires_mask; int /*<<< orphan*/  longname; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  nn_option_requires (struct nn_parse_context*,int) ; 
 int /*<<< orphan*/  nn_print_requires (struct nn_parse_context*,int) ; 
 int /*<<< orphan*/  stderr ; 

void nn_check_requires (struct nn_parse_context *ctx) {
    int i;
    struct nn_option *opt;

    for (i = 0;; ++i) {
        opt = &ctx->options[i];
        if (!opt->longname)
            break;
        if (!ctx->last_option_usage[i])
            continue;
        if (opt->requires_mask &&
            (opt->requires_mask & ctx->mask) != opt->requires_mask) {
            nn_option_requires (ctx, i);
        }
    }

    if ((ctx->requires & ctx->mask) != ctx->requires) {
        fprintf (stderr, "%s: At least one of the following required:\n",
            ctx->argv[0]);
        nn_print_requires (ctx, ctx->requires & ~ctx->mask);
        exit (1);
    }
}