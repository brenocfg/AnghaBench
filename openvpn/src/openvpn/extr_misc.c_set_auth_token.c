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
struct user_pass {int defined; char const* password; char const* username; } ;

/* Variables and functions */
 int /*<<< orphan*/  USER_PASS_LEN ; 
 int /*<<< orphan*/  purge_user_pass (struct user_pass*,int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpynt (char const*,char const*,int /*<<< orphan*/ ) ; 

void
set_auth_token(struct user_pass *up, struct user_pass *tk, const char *token)
{

    if (token && strlen(token) && up && up->defined)
    {
        strncpynt(tk->password, token, USER_PASS_LEN);
        strncpynt(tk->username, up->username, USER_PASS_LEN);
        tk->defined = true;
    }

    /* Cleans user/pass for nocache */
    purge_user_pass(up, false);
}