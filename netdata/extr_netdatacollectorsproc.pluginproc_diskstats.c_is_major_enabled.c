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
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MAX_NAME ; 
 int /*<<< orphan*/  CONFIG_SECTION_PLUGIN_PROC_DISKSTATS ; 
 scalar_t__ config_get_boolean (int /*<<< orphan*/ ,char*,int) ; 
 int* reallocz (int*,size_t) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline int is_major_enabled(int major) {
    static int8_t *major_configs = NULL;
    static size_t major_size = 0;

    if(major < 0) return 1;

    size_t wanted_size = (size_t)major + 1;

    if(major_size < wanted_size) {
        major_configs = reallocz(major_configs, wanted_size * sizeof(int8_t));

        size_t i;
        for(i = major_size; i < wanted_size ; i++)
            major_configs[i] = -1;

        major_size = wanted_size;
    }

    if(major_configs[major] == -1) {
        char buffer[CONFIG_MAX_NAME + 1];
        snprintfz(buffer, CONFIG_MAX_NAME, "performance metrics for disks with major %d", major);
        major_configs[major] = (char)config_get_boolean(CONFIG_SECTION_PLUGIN_PROC_DISKSTATS, buffer, 1);
    }

    return (int)major_configs[major];
}