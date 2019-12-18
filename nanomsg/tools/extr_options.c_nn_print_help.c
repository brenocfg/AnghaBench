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
struct nn_parse_context {struct nn_option* options; TYPE_1__* def; } ;
struct nn_option {char* longname; char* group; int shortname; char* metavar; char* description; } ;
struct TYPE_2__ {char* short_description; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ nn_has_arg (struct nn_option*) ; 
 char* nn_print_line (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nn_print_usage (struct nn_parse_context*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void nn_print_help (struct nn_parse_context *ctx, FILE *stream)
{
    int i;
    size_t optlen;
    struct nn_option *opt;
    char *last_group;
    char *cursor;

    fprintf (stream, "Usage:\n");
    nn_print_usage (ctx, stream);
    fprintf (stream, "\n%s\n", ctx->def->short_description);

    last_group = NULL;
    for (i = 0;; ++i) {
        opt = &ctx->options[i];
        if (!opt->longname)
            break;
        if (!last_group || last_group != opt->group ||
            strcmp (last_group, opt->group))
        {
            fprintf (stream, "\n");
            fprintf (stream, "%s:\n", opt->group);
            last_group = opt->group;
        }
        fprintf (stream, " --%s", opt->longname);
        optlen = 3 + strlen (opt->longname);
        if (opt->shortname) {
            fprintf (stream, ",-%c", opt->shortname);
            optlen += 3;
        }
        if (nn_has_arg (opt)) {
            if (opt->metavar) {
                fprintf (stream, " %s", opt->metavar);
                optlen += strlen (opt->metavar) + 1;
            } else {
                fprintf (stream, " ARG");
                optlen += 4;
            }
        }
        if (optlen < 23) {
            fputs (&"                        "[optlen], stream);
            cursor = nn_print_line (stream, opt->description, 80-24);
        } else {
            cursor = opt->description;
        }
        while (*cursor) {
            fprintf (stream, "\n                        ");
            cursor = nn_print_line (stream, cursor, 80-24);
        }
        fprintf (stream, "\n");
    }
}