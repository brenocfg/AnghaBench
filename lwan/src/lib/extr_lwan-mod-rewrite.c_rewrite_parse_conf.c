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
struct private_data {int dummy; } ;
struct config_line {int type; int /*<<< orphan*/  key; } ;
struct config {int dummy; } ;

/* Variables and functions */
#define  CONFIG_LINE_TYPE_LINE 130 
#define  CONFIG_LINE_TYPE_SECTION 129 
#define  CONFIG_LINE_TYPE_SECTION_END 128 
 int /*<<< orphan*/  config_error (struct config*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_last_error (struct config*) ; 
 struct config_line* config_read_line (struct config*) ; 
 int /*<<< orphan*/  rewrite_parse_conf_pattern (struct private_data*,struct config*,struct config_line const*) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool rewrite_parse_conf(void *instance, struct config *config)
{
    struct private_data *pd = instance;
    const struct config_line *line;

    while ((line = config_read_line(config))) {
        switch (line->type) {
        case CONFIG_LINE_TYPE_LINE:
            config_error(config, "Unknown option: %s", line->key);
            break;
        case CONFIG_LINE_TYPE_SECTION:
            if (streq(line->key, "pattern")) {
                rewrite_parse_conf_pattern(pd, config, line);
            } else {
                config_error(config, "Unknown section: %s", line->key);
            }
            break;
        case CONFIG_LINE_TYPE_SECTION_END:
            break;
        }
    }

    return !config_last_error(config);
}