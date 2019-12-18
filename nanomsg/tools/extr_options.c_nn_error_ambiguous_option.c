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
struct nn_parse_context {char* data; char** argv; struct nn_option* options; } ;
struct nn_option {char* longname; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void nn_error_ambiguous_option (struct nn_parse_context *ctx)
{
    struct nn_option *opt;
    char *a, *b;
    char *arg;

    arg = ctx->data+2;
    fprintf (stderr, "%s: Ambiguous option ``%s'':\n", ctx->argv[0], ctx->data);
    for (opt = ctx->options; opt->longname; ++opt) {
        for (a = opt->longname, b = arg; ; ++a, ++b) {
            if (*b == 0 || *b == '=') {  /* End of option on command-line */
                fprintf (stderr, "    %s\n", opt->longname);
                break;
            } else if (*b != *a) {
                break;
            }
        }
    }
    exit (1);
}