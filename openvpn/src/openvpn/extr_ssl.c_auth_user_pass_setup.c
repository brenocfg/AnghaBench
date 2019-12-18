#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct static_challenge_info {int flags; scalar_t__ challenge_text; } ;
struct TYPE_6__ {int /*<<< orphan*/  defined; } ;
struct TYPE_5__ {int /*<<< orphan*/  defined; } ;

/* Variables and functions */
 int GET_USER_PASS_DYNAMIC_CHALLENGE ; 
 int GET_USER_PASS_MANAGEMENT ; 
 int GET_USER_PASS_STATIC_CHALLENGE ; 
 int GET_USER_PASS_STATIC_CHALLENGE_ECHO ; 
 int SC_ECHO ; 
 int /*<<< orphan*/  UP_TYPE_AUTH ; 
 scalar_t__ auth_challenge ; 
 TYPE_4__ auth_token ; 
 TYPE_1__ auth_user_pass ; 
 int auth_user_pass_enabled ; 
 int /*<<< orphan*/  get_user_pass (TYPE_1__*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_user_pass_cr (TYPE_1__*,char const*,int /*<<< orphan*/ ,int,scalar_t__) ; 

void
auth_user_pass_setup(const char *auth_file, const struct static_challenge_info *sci)
{
    auth_user_pass_enabled = true;
    if (!auth_user_pass.defined && !auth_token.defined)
    {
#ifdef ENABLE_MANAGEMENT
        if (auth_challenge) /* dynamic challenge/response */
        {
            get_user_pass_cr(&auth_user_pass,
                             auth_file,
                             UP_TYPE_AUTH,
                             GET_USER_PASS_MANAGEMENT|GET_USER_PASS_DYNAMIC_CHALLENGE,
                             auth_challenge);
        }
        else if (sci) /* static challenge response */
        {
            int flags = GET_USER_PASS_MANAGEMENT|GET_USER_PASS_STATIC_CHALLENGE;
            if (sci->flags & SC_ECHO)
            {
                flags |= GET_USER_PASS_STATIC_CHALLENGE_ECHO;
            }
            get_user_pass_cr(&auth_user_pass,
                             auth_file,
                             UP_TYPE_AUTH,
                             flags,
                             sci->challenge_text);
        }
        else
#endif /* ifdef ENABLE_MANAGEMENT */
        get_user_pass(&auth_user_pass, auth_file, UP_TYPE_AUTH, GET_USER_PASS_MANAGEMENT);
    }
}