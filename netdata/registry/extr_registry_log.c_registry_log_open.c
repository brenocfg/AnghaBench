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
struct TYPE_2__ {int /*<<< orphan*/  log_filename; scalar_t__ log_fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ fopen (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ registry ; 
 scalar_t__ setvbuf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int registry_log_open(void) {
    if(registry.log_fp)
        fclose(registry.log_fp);

    registry.log_fp = fopen(registry.log_filename, "a");
    if(registry.log_fp) {
        if (setvbuf(registry.log_fp, NULL, _IOLBF, 0) != 0)
            error("Cannot set line buffering on registry log file.");
        return 0;
    }

    error("Cannot open registry log file '%s'. Registry data will be lost in case of netdata or server crash.", registry.log_filename);
    return -1;
}