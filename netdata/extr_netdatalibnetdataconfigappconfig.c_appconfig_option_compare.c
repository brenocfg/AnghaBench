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
struct config_option {scalar_t__ hash; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int appconfig_option_compare(void *a, void *b) {
    if(((struct config_option *)a)->hash < ((struct config_option *)b)->hash) return -1;
    else if(((struct config_option *)a)->hash > ((struct config_option *)b)->hash) return 1;
    else return strcmp(((struct config_option *)a)->name, ((struct config_option *)b)->name);
}