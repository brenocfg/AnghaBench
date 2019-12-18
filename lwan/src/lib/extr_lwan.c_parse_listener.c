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
struct lwan_module {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  listener; } ;
struct lwan {TYPE_1__ config; } ;
struct config_line {int type; char* key; int /*<<< orphan*/  value; } ;
struct config {int dummy; } ;

/* Variables and functions */
#define  CONFIG_LINE_TYPE_LINE 130 
#define  CONFIG_LINE_TYPE_SECTION 129 
#define  CONFIG_LINE_TYPE_SECTION_END 128 
 int /*<<< orphan*/  config_error (struct config*,char*,...) ; 
 struct config_line* config_read_line (struct config*) ; 
 void* find_handler (int /*<<< orphan*/ ) ; 
 struct lwan_module* find_module (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_listener_prefix (struct config*,struct config_line const*,struct lwan*,struct lwan_module const*,void*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_listener(struct config *c,
                           const struct config_line *l,
                           struct lwan *lwan)
{
    free(lwan->config.listener);
    lwan->config.listener = strdup(l->value);

    while ((l = config_read_line(c))) {
        switch (l->type) {
        case CONFIG_LINE_TYPE_LINE:
            config_error(c, "Expecting prefix section");
            return;
        case CONFIG_LINE_TYPE_SECTION:
            if (l->key[0] == '&') {
                void *handler = find_handler(l->key + 1);
                if (handler) {
                    parse_listener_prefix(c, l, lwan, NULL, handler);
                    continue;
                }

                config_error(c, "Could not find handler name: %s", l->key + 1);
                return;
            }

            const struct lwan_module *module = find_module(l->key);
            if (module) {
                parse_listener_prefix(c, l, lwan, module, NULL);
                continue;
            }

            config_error(c, "Invalid section or module not found: %s", l->key);
            return;
        case CONFIG_LINE_TYPE_SECTION_END:
            return;
        }
    }

    config_error(c, "Expecting section end while parsing listener");
}