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
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug_record (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tapping_key ; 

__attribute__((used)) static void debug_tapping_key(void) {
    debug("TAPPING_KEY=");
    debug_record(tapping_key);
    debug("\n");
}