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
struct nn_parse_context {char* data; char** last_option_usage; struct nn_option* options; } ;
struct nn_option {char* longname; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_error_ambiguous_option (struct nn_parse_context*) ; 
 int /*<<< orphan*/  nn_error_unknown_long_option (struct nn_parse_context*) ; 
 scalar_t__ nn_get_arg (struct nn_parse_context*) ; 
 scalar_t__ nn_has_arg (struct nn_option*) ; 
 int /*<<< orphan*/  nn_option_error (char*,struct nn_parse_context*,int) ; 
 int /*<<< orphan*/  nn_process_option (struct nn_parse_context*,int,char*) ; 

__attribute__((used)) static void nn_parse_long_option (struct nn_parse_context *ctx)
{
    struct nn_option *opt;
    char *a, *b;
    size_t longest_prefix;
    size_t cur_prefix;
    int best_match;
    char *arg;
    int i;

    arg = ctx->data+2;
    longest_prefix = 0;
    best_match = -1;
    for (i = 0;; ++i) {
        opt = &ctx->options[i];
        if (!opt->longname)
            break;
        for (a = opt->longname, b = arg;; ++a, ++b) {
            if (*b == 0 || *b == '=') {  /* End of option on command-line */
                cur_prefix = a - opt->longname;
                if (!*a) {  /* Matches end of option name */
                    best_match = i;
                    longest_prefix = cur_prefix;
                    goto finish;
                }
                if (cur_prefix == longest_prefix) {
                    best_match = -1;  /* Ambiguity */
                } else if (cur_prefix > longest_prefix) {
                    best_match = i;
                    longest_prefix = cur_prefix;
                }
                break;
            } else if (*b != *a) {
                break;
            }
        }
    }
finish:
    if (best_match >= 0) {
        opt = &ctx->options[best_match];
        ctx->last_option_usage[best_match] = ctx->data;
        if (arg[longest_prefix] == '=') {
            if (nn_has_arg (opt)) {
                nn_process_option (ctx, best_match, arg + longest_prefix + 1);
            } else {
                nn_option_error ("does not accept argument", ctx, best_match);
            }
        } else {
            if (nn_has_arg (opt)) {
                if (nn_get_arg (ctx)) {
                    nn_process_option (ctx, best_match, ctx->data);
                } else {
                    nn_option_error ("requires an argument", ctx, best_match);
                }
            } else {
                nn_process_option (ctx, best_match, NULL);
            }
        }
    } else if (longest_prefix > 0) {
        nn_error_ambiguous_option (ctx);
    } else {
        nn_error_unknown_long_option (ctx);
    }
}