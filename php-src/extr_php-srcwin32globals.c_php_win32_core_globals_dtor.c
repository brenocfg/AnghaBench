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
struct TYPE_2__ {scalar_t__ mail_socket; int /*<<< orphan*/ * registry_directories; int /*<<< orphan*/ * registry_event; int /*<<< orphan*/ * registry_key; } ;
typedef  TYPE_1__ php_win32_core_globals ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ *) ; 

void php_win32_core_globals_dtor(void *vg)
{/*{{{*/
	php_win32_core_globals *wg = (php_win32_core_globals*)vg;

	if (wg->registry_key) {
		RegCloseKey(wg->registry_key);
		wg->registry_key = NULL;
	}
	if (wg->registry_event) {
		CloseHandle(wg->registry_event);
		wg->registry_event = NULL;
	}
	if (wg->registry_directories) {
		zend_hash_destroy(wg->registry_directories);
		free(wg->registry_directories);
		wg->registry_directories = NULL;
	}

	if (INVALID_SOCKET != wg->mail_socket) {
		closesocket(wg->mail_socket);
		wg->mail_socket = INVALID_SOCKET;
	}
}