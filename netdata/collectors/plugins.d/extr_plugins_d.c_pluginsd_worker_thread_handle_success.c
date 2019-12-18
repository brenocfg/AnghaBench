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
struct plugind {int successful_collections; int update_every; scalar_t__ serial_failures; char* pid; scalar_t__ enabled; int /*<<< orphan*/  fullfilename; } ;

/* Variables and functions */
 scalar_t__ SERIAL_FAILURES_THRESHOLD ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sleep (unsigned int) ; 

__attribute__((used)) static void pluginsd_worker_thread_handle_success(struct plugind *cd) {
    if (likely(cd->successful_collections)) {
        sleep((unsigned int) cd->update_every);
        return;
    }

    if(likely(cd->serial_failures <= SERIAL_FAILURES_THRESHOLD)) {
        info("'%s' (pid %d) does not generate useful output but it reports success (exits with 0). %s.",
            cd->fullfilename, cd->pid,
            cd->enabled ?
                "Waiting a bit before starting it again." :
                "Will not start it again - it is now disabled.");
        sleep((unsigned int) (cd->update_every * 10));
        return;
    }

    if (cd->serial_failures > SERIAL_FAILURES_THRESHOLD) {
        error("'%s' (pid %d) does not generate useful output, although it reports success (exits with 0)."
            "We have tried to collect something %zu times - unsuccessfully. Disabling it.",
            cd->fullfilename, cd->pid, cd->serial_failures);
        cd->enabled = 0;
        return;
    }

    return;
}