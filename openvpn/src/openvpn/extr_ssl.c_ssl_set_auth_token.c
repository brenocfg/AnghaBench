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
 int /*<<< orphan*/  auth_token ; 
 int /*<<< orphan*/  auth_user_pass ; 
 int /*<<< orphan*/  set_auth_token (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

void
ssl_set_auth_token(const char *token)
{
    set_auth_token(&auth_user_pass, &auth_token, token);
}