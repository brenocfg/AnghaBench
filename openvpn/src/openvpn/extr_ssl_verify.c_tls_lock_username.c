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
struct tls_multi {scalar_t__ locked_username; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TLS_ERRORS ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  np (char const*) ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 
 scalar_t__ string_alloc (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_deauthenticate (struct tls_multi*) ; 

__attribute__((used)) static bool
tls_lock_username(struct tls_multi *multi, const char *username)
{
    if (multi->locked_username)
    {
        if (!username || strcmp(username, multi->locked_username))
        {
            msg(D_TLS_ERRORS, "TLS Auth Error: username attempted to change from '%s' to '%s' -- tunnel disabled",
                multi->locked_username,
                np(username));

            /* disable the tunnel */
            tls_deauthenticate(multi);
            return false;
        }
    }
    else
    {
        if (username)
        {
            multi->locked_username = string_alloc(username, NULL);
        }
    }
    return true;
}