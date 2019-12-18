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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SECTION_HEALTH ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  config_get (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  netdata_configured_varlib_dir ; 
 int /*<<< orphan*/  silencers_filename ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void set_silencers_filename() {
    char filename[FILENAME_MAX + 1];
    snprintfz(filename, FILENAME_MAX, "%s/health.silencers.json", netdata_configured_varlib_dir);
    silencers_filename = config_get(CONFIG_SECTION_HEALTH, "silencers file", filename);
}