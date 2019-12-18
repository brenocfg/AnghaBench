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
 int /*<<< orphan*/  auth_token_pem_name ; 
 int /*<<< orphan*/  write_pem_key_file (char const*,int /*<<< orphan*/ ) ; 

void
auth_token_write_server_key_file(const char *filename)
{
    write_pem_key_file(filename, auth_token_pem_name);
}