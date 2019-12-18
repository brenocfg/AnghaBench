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
struct TYPE_2__ {int /*<<< orphan*/ * log_fp; int /*<<< orphan*/  log_filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ registry ; 
 int /*<<< orphan*/  registry_log_close () ; 
 int /*<<< orphan*/  registry_log_open () ; 

void registry_log_recreate(void) {
    if(registry.log_fp != NULL) {
        registry_log_close();

        // open it with truncate
        registry.log_fp = fopen(registry.log_filename, "w");
        if(registry.log_fp) fclose(registry.log_fp);
        else error("Cannot truncate registry log '%s'", registry.log_filename);

        registry.log_fp = NULL;
        registry_log_open();
    }
}