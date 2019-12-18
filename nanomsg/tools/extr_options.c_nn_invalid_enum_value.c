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
struct nn_parse_context {char** argv; struct nn_option* options; } ;
struct nn_option {scalar_t__ pointer; } ;
struct nn_enum_item {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nn_print_option (struct nn_parse_context*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void nn_invalid_enum_value (struct nn_parse_context *ctx,
    int opt_index, char *argument)
{
    struct nn_option *opt;
    struct nn_enum_item *items;

    opt = &ctx->options[opt_index];
    items = (struct nn_enum_item *)opt->pointer;
    fprintf (stderr, "%s: Invalid value ``%s'' for", ctx->argv[0], argument);
    nn_print_option (ctx, opt_index, stderr);
    fprintf (stderr, ". Options are:\n");
    for (;items->name; ++items) {
        fprintf (stderr, "    %s\n", items->name);
    }
    exit (1);
}