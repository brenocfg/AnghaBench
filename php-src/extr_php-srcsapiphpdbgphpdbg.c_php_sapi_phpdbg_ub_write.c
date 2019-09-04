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
 int PHPDBG_G (int /*<<< orphan*/ ) ; 
 int PHPDBG_IS_INTERACTIVE ; 
 int /*<<< orphan*/  P_STDOUT ; 
 int /*<<< orphan*/  flags ; 
 size_t phpdbg_script (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  send (int,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_fd ; 

__attribute__((used)) static inline size_t php_sapi_phpdbg_ub_write(const char *message, size_t length) /* {{{ */
{
	if (PHPDBG_G(socket_fd) != -1 && !(PHPDBG_G(flags) & PHPDBG_IS_INTERACTIVE)) {
		send(PHPDBG_G(socket_fd), message, length, 0);
	}
	return phpdbg_script(P_STDOUT, "%.*s", (int) length, message);
}