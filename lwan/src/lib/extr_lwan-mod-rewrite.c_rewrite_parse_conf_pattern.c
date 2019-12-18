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
struct private_data {int /*<<< orphan*/  patterns; } ;
struct pattern {char* pattern; char* expand_pattern; int /*<<< orphan*/  flags; } ;
struct config_line {int type; int /*<<< orphan*/  key; int /*<<< orphan*/  value; } ;
struct config {int dummy; } ;

/* Variables and functions */
#define  CONFIG_LINE_TYPE_LINE 130 
#define  CONFIG_LINE_TYPE_SECTION 129 
#define  CONFIG_LINE_TYPE_SECTION_END 128 
 int /*<<< orphan*/  PATTERN_EXPAND_LUA ; 
 int /*<<< orphan*/  PATTERN_EXPAND_LWAN ; 
 int /*<<< orphan*/  PATTERN_HANDLE_REDIRECT ; 
 int /*<<< orphan*/  PATTERN_HANDLE_REWRITE ; 
 int /*<<< orphan*/  config_error (struct config*,char*,...) ; 
 struct config_line* config_read_line (struct config*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int parse_bool (int /*<<< orphan*/ ,int) ; 
 struct pattern* pattern_array_append0 (int /*<<< orphan*/ *) ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool rewrite_parse_conf_pattern(struct private_data *pd,
                                       struct config *config,
                                       const struct config_line *line)
{
    struct pattern *pattern;
    char *redirect_to = NULL, *rewrite_as = NULL;
    bool expand_with_lua = false;

    pattern = pattern_array_append0(&pd->patterns);
    if (!pattern)
        goto out_no_free;

    pattern->pattern = strdup(line->value);
    if (!pattern->pattern)
        goto out;

    while ((line = config_read_line(config))) {
        switch (line->type) {
        case CONFIG_LINE_TYPE_LINE:
            if (streq(line->key, "redirect_to")) {
                free(redirect_to);

                redirect_to = strdup(line->value);
                if (!redirect_to)
                    goto out;
            } else if (streq(line->key, "rewrite_as")) {
                free(rewrite_as);

                rewrite_as = strdup(line->value);
                if (!rewrite_as)
                    goto out;
            } else if (streq(line->key, "expand_with_lua")) {
                expand_with_lua = parse_bool(line->value, false);
            } else {
                config_error(config, "Unexpected key: %s", line->key);
                goto out;
            }
            break;
        case CONFIG_LINE_TYPE_SECTION:
            config_error(config, "Unexpected section: %s", line->key);
            break;
        case CONFIG_LINE_TYPE_SECTION_END:
            if (redirect_to && rewrite_as) {
                config_error(
                    config,
                    "`redirect to` and `rewrite as` are mutually exclusive");
                goto out;
            }
            if (redirect_to) {
                pattern->expand_pattern = redirect_to;
                pattern->flags |= PATTERN_HANDLE_REDIRECT;
            } else if (rewrite_as) {
                pattern->expand_pattern = rewrite_as;
                pattern->flags |= PATTERN_HANDLE_REWRITE;
            } else {
                config_error(
                    config,
                    "either `redirect to` or `rewrite as` are required");
                goto out;
            }
            if (expand_with_lua) {
#ifdef HAVE_LUA
                pattern->flags |= PATTERN_EXPAND_LUA;
#else
                config_error(config, "Lwan has been built without Lua. "
                                     "`expand_with_lua` is not available");
                goto out;
#endif
            } else {
                pattern->flags |= PATTERN_EXPAND_LWAN;
            }

            return true;
        }
    }

out:
    free(pattern->pattern);
    free(redirect_to);
    free(rewrite_as);
out_no_free:
    config_error(config, "Could not copy pattern");
    return false;
}