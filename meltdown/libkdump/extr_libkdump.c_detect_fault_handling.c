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
struct TYPE_2__ {int /*<<< orphan*/  fault_handling; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  SIGNAL_HANDLER ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  TSX ; 
 scalar_t__ check_tsx () ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void detect_fault_handling() {
  if (check_tsx()) {
    debug(SUCCESS, "Using Intel TSX\n");
    config.fault_handling = TSX;
  } else {
    debug(INFO, "No Intel TSX, fallback to signal handler\n");
    config.fault_handling = SIGNAL_HANDLER;
  }
}