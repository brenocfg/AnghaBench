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
struct nn_parse_context {char** argv; TYPE_1__* options; } ;
struct TYPE_2__ {int /*<<< orphan*/  requires_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nn_print_option (struct nn_parse_context*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_print_requires (struct nn_parse_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void nn_option_requires (struct nn_parse_context *ctx, int opt_index) {
    fprintf (stderr, "%s: Option", ctx->argv[0]);
    nn_print_option (ctx, opt_index, stderr);
    fprintf (stderr, "requires at least one of the following options:\n");

    nn_print_requires (ctx, ctx->options[opt_index].requires_mask);
    exit (1);
}