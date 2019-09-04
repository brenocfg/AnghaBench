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
struct config_pair {int /*<<< orphan*/  key; } ;
struct config_option {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int ARRAYSIZE (struct config_option*) ; 
 int ERROR_NOT_FOUND ; 
 int NO_ERROR ; 
 struct config_option* g_options ; 
 scalar_t__ stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_find_option(
    const struct config_pair *pair,
    const struct config_option **option)
{
    int i, count = ARRAYSIZE(g_options);
    int status = ERROR_NOT_FOUND;

    /* find the config_option by key */
    for (i = 0; i < count; i++) {
        if (stricmp(pair->key, g_options[i].key) == 0) {
            *option = &g_options[i];
            status = NO_ERROR;
            break;
        }
    }
    return status;
}