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
 scalar_t__ SERVERS_USER_PASS_LEN_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mp_raise_ValueError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpexception_value_invalid_arguments ; 
 int /*<<< orphan*/  servers_pass ; 
 int /*<<< orphan*/  servers_user ; 
 scalar_t__ strlen (char*) ; 

void servers_set_login (char *user, char *pass) {
    if (strlen(user) > SERVERS_USER_PASS_LEN_MAX || strlen(pass) > SERVERS_USER_PASS_LEN_MAX) {
        mp_raise_ValueError(mpexception_value_invalid_arguments);
    }
    memcpy(servers_user, user, SERVERS_USER_PASS_LEN_MAX);
    memcpy(servers_pass, pass, SERVERS_USER_PASS_LEN_MAX);
}