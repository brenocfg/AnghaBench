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
struct ssl_conf_name_st {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct ssl_conf_name_st* ssl_names ; 
 size_t ssl_names_count ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int conf_ssl_name_find(const char *name, size_t *idx)
{
    size_t i;
    const struct ssl_conf_name_st *nm;

    if (name == NULL)
        return 0;
    for (i = 0, nm = ssl_names; i < ssl_names_count; i++, nm++) {
        if (strcmp(nm->name, name) == 0) {
            *idx = i;
            return 1;
        }
    }
    return 0;
}