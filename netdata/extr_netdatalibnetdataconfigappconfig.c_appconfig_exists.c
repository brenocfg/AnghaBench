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
struct section {int dummy; } ;
struct config_option {int dummy; } ;
struct config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONFIG ; 
 struct config_option* appconfig_option_index_find (struct section*,char const*,int /*<<< orphan*/ ) ; 
 struct section* appconfig_section_find (struct config*,char const*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,char const*) ; 

int appconfig_exists(struct config *root, const char *section, const char *name) {
    struct config_option *cv;

    debug(D_CONFIG, "request to get config in section '%s', name '%s'", section, name);

    struct section *co = appconfig_section_find(root, section);
    if(!co) return 0;

    cv = appconfig_option_index_find(co, name, 0);
    if(!cv) return 0;

    return 1;
}