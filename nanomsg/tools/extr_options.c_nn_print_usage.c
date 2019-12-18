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
struct nn_parse_context {char** argv; int requires; struct nn_option* options; } ;
struct nn_option {char* longname; int mask_set; int shortname; char* metavar; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ nn_has_arg (struct nn_option*) ; 

__attribute__((used)) static void nn_print_usage (struct nn_parse_context *ctx, FILE *stream)
{
    int i;
    int first;
    struct nn_option *opt;

    fprintf (stream, "    %s ", ctx->argv[0]);

    /* Print required options (long names)  */
    first = 1;
    for (i = 0;; ++i) {
        opt = &ctx->options[i];
        if (!opt->longname)
            break;
        if (opt->mask_set & ctx->requires) {
            if (first) {
                first = 0;
                fprintf (stream, "{--%s", opt->longname);
            } else {
                fprintf (stream, "|--%s", opt->longname);
            }
        }
    }
    if (!first) {
        fprintf (stream, "} ");
    }

    /* Print flag short options */
    first = 1;
    for (i = 0;; ++i) {
        opt = &ctx->options[i];
        if (!opt->longname)
            break;
        if (opt->mask_set & ctx->requires)
            continue;  /* already printed */
        if (opt->shortname && !nn_has_arg (opt)) {
            if (first) {
                first = 0;
                fprintf (stream, "[-%c", opt->shortname);
            } else {
                fprintf (stream, "%c", opt->shortname);
            }
        }
    }
    if (!first) {
        fprintf (stream, "] ");
    }

    /* Print short options with arguments */
    for (i = 0;; ++i) {
        opt = &ctx->options[i];
        if (!opt->longname)
            break;
        if (opt->mask_set & ctx->requires)
            continue;  /* already printed */
        if (opt->shortname && nn_has_arg (opt) && opt->metavar) {
            fprintf (stream, "[-%c %s] ", opt->shortname, opt->metavar);
        }
    }

    fprintf (stream, "[options] \n");  /* There may be long options too */
}