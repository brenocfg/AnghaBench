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
struct TYPE_2__ {scalar_t__ cache_miss_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIME ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  detect_flush_reload_threshold () ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int check_config() {
  if (config.cache_miss_threshold <= 0) {
    detect_flush_reload_threshold();
  }
  if (config.cache_miss_threshold <= 0) {
    errno = ETIME;
    return -1;
  }
  return 0;
}