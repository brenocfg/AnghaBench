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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phpdbg_close_socket (int) ; 

__attribute__((used)) static void phpdbg_remote_close(int socket, FILE *stream) {
	if (socket >= 0) {
		phpdbg_close_socket(socket);
	}

	if (stream) {
		fclose(stream);
	}
}