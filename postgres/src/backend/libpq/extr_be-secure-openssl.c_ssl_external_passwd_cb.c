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
 int /*<<< orphan*/  Assert (int) ; 
 int run_ssl_passphrase_command (char const*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ssl_is_server_start ; 

__attribute__((used)) static int
ssl_external_passwd_cb(char *buf, int size, int rwflag, void *userdata)
{
	/* same prompt as OpenSSL uses internally */
	const char *prompt = "Enter PEM pass phrase:";

	Assert(rwflag == 0);

	return run_ssl_passphrase_command(prompt, ssl_is_server_start, buf, size);
}