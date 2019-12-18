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
 int /*<<< orphan*/  auth_user_pass ; 
 int /*<<< orphan*/  passbuf ; 
 int /*<<< orphan*/  pkcs11_logout () ; 
 int /*<<< orphan*/  purge_user_pass (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ssl_purge_auth_challenge () ; 

void
ssl_purge_auth(const bool auth_user_pass_only)
{
    if (!auth_user_pass_only)
    {
#ifdef ENABLE_PKCS11
        pkcs11_logout();
#endif
        purge_user_pass(&passbuf, true);
    }
    purge_user_pass(&auth_user_pass, true);
#ifdef ENABLE_MANAGEMENT
    ssl_purge_auth_challenge();
#endif
}