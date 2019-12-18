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
struct TYPE_2__ {void* password_file; void* realm; } ;
struct lwan_url_map {TYPE_1__ authorization; int /*<<< orphan*/  flags; } ;
struct config_line {char* value; int type; char* key; } ;
struct config {int dummy; } ;

/* Variables and functions */
#define  CONFIG_LINE_TYPE_LINE 130 
#define  CONFIG_LINE_TYPE_SECTION 129 
#define  CONFIG_LINE_TYPE_SECTION_END 128 
 int /*<<< orphan*/  HANDLER_MUST_AUTHORIZE ; 
 int /*<<< orphan*/  config_error (struct config*,char*,...) ; 
 struct config_line* config_read_line (struct config*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* strdup (char*) ; 
 scalar_t__ streq (char*,char*) ; 

__attribute__((used)) static void parse_listener_prefix_authorization(struct config *c,
                                                const struct config_line *l,
                                                struct lwan_url_map *url_map)
{
    if (!streq(l->value, "basic")) {
        config_error(c, "Only basic authorization supported");
        return;
    }

    memset(&url_map->authorization, 0, sizeof(url_map->authorization));

    while ((l = config_read_line(c))) {
        switch (l->type) {
        case CONFIG_LINE_TYPE_LINE:
            if (streq(l->key, "realm")) {
                free(url_map->authorization.realm);
                url_map->authorization.realm = strdup(l->value);
            } else if (streq(l->key, "password_file")) {
                free(url_map->authorization.password_file);
                url_map->authorization.password_file = strdup(l->value);
            }
            break;

        case CONFIG_LINE_TYPE_SECTION:
            config_error(c, "Unexpected section: %s", l->key);
            goto error;

        case CONFIG_LINE_TYPE_SECTION_END:
            if (!url_map->authorization.realm)
                url_map->authorization.realm = strdup("Lwan");
            if (!url_map->authorization.password_file)
                url_map->authorization.password_file = strdup("htpasswd");

            url_map->flags |= HANDLER_MUST_AUTHORIZE;
            return;
        }
    }

    config_error(c, "Could not find end of authorization section");

error:
    free(url_map->authorization.realm);
    free(url_map->authorization.password_file);
}