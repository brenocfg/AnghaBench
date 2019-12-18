#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  os_target; int /*<<< orphan*/  raw; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeconfig_read_user () ; 
 TYPE_2__ runtime_userspace_config ; 
 int /*<<< orphan*/  set_os (int /*<<< orphan*/ ) ; 
 TYPE_1__ stored_userspace_config ; 

void matrix_init_user(void) {
  stored_userspace_config.raw = eeconfig_read_user();
  runtime_userspace_config.raw = stored_userspace_config.raw;

  set_os(runtime_userspace_config.os_target);
}