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
struct nn_parse_context {char** argv; char** last_option_usage; struct nn_option* options; } ;
struct nn_option {scalar_t__ arg0name; int /*<<< orphan*/  longname; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nn_has_arg (struct nn_option*) ; 
 int /*<<< orphan*/  nn_process_option (struct nn_parse_context*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,scalar_t__) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void nn_parse_arg0 (struct nn_parse_context *ctx)
{
    int i;
    struct nn_option *opt;
    char *arg0;

    arg0 = strrchr (ctx->argv[0], '/');
    if (arg0 == NULL) {
        arg0 = ctx->argv[0];
    } else {
        arg0 += 1; /*  Skip slash itself  */
    }


    for (i = 0;; ++i) {
        opt = &ctx->options[i];
        if (!opt->longname)
            return;
        if (opt->arg0name && !strcmp (arg0, opt->arg0name)) {
            assert (!nn_has_arg (opt));
            ctx->last_option_usage[i] = ctx->argv[0];
            nn_process_option (ctx, i, NULL);
        }
    }
}