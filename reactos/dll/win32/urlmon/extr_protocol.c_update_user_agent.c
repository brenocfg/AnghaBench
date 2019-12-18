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
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  INTERNET_OPTION_USER_AGENT ; 
 int /*<<< orphan*/  InternetSetOptionW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ internet_session ; 
 int /*<<< orphan*/  strlenW (int /*<<< orphan*/ *) ; 

void update_user_agent(WCHAR *user_agent)
{
    if(internet_session)
        InternetSetOptionW(internet_session, INTERNET_OPTION_USER_AGENT, user_agent, strlenW(user_agent));
}