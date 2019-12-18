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
typedef  int uint8_t ;
struct TYPE_2__ {int os_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  UC_LNX ; 
 int /*<<< orphan*/  UC_OSX ; 
 int /*<<< orphan*/  UC_WIN ; 
#define  _OS_LINUX 130 
#define  _OS_MACOS 129 
#define  _OS_WINDOWS 128 
 TYPE_1__ runtime_userspace_config ; 
 int /*<<< orphan*/  set_unicode_input_mode (int /*<<< orphan*/ ) ; 

void set_os(uint8_t os) {
  runtime_userspace_config.os_target = os;

  switch (os) {
  case _OS_MACOS:
    set_unicode_input_mode(UC_OSX);
    break;
  case _OS_LINUX:
    set_unicode_input_mode(UC_LNX);
    break;
  case _OS_WINDOWS:
    set_unicode_input_mode(UC_WIN);
    break;
  }
}