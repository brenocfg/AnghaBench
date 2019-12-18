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
 scalar_t__ STDIN_BUF_SIZE ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__* stdin_buf ; 
 char* strdup (scalar_t__*) ; 
 int strlen (scalar_t__*) ; 

__attribute__((used)) static char *stdin_gets() {
#define STDIN_BUF_SIZE 96096
	if (!stdin_buf) {
		/* XXX: never freed. leaks! */
		stdin_buf = malloc (STDIN_BUF_SIZE);
		if (!stdin_buf) {
			return NULL;
		}
	}
	memset (stdin_buf, 0, STDIN_BUF_SIZE);
	if (!fgets (stdin_buf, STDIN_BUF_SIZE - 1, stdin)) {
		return NULL;
	}
	if (feof (stdin)) {
		return NULL;
	}
	stdin_buf[strlen (stdin_buf) - 1] = 0;
	return strdup (stdin_buf);
}