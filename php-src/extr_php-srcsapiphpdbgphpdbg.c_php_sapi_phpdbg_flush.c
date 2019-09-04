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
struct TYPE_2__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 TYPE_1__* PHPDBG_G (int /*<<< orphan*/ ) ; 
 size_t PHPDBG_STDOUT ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io ; 
 int /*<<< orphan*/  phpdbg_active_sigsafe_mem () ; 

__attribute__((used)) static inline void php_sapi_phpdbg_flush(void *context)  /* {{{ */
{
	if (!phpdbg_active_sigsafe_mem()) {
		fflush(PHPDBG_G(io)[PHPDBG_STDOUT].ptr);
	}
}