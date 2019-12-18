#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  defined; } ;
struct TYPE_4__ {int /*<<< orphan*/  auth_file; scalar_t__ inline_creds; } ;
struct http_proxy_info {int queried_creds; TYPE_2__ up; TYPE_1__ options; } ;

/* Variables and functions */
 unsigned int GET_USER_PASS_INLINE_CREDS ; 
 unsigned int GET_USER_PASS_MANAGEMENT ; 
 unsigned int GET_USER_PASS_PREVIOUS_CREDS_FAILED ; 
 int /*<<< orphan*/  UP_TYPE_PROXY ; 
 int /*<<< orphan*/  clear_user_pass_http () ; 
 int /*<<< orphan*/  get_user_pass (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__ static_proxy_user_pass ; 

__attribute__((used)) static void
get_user_pass_http(struct http_proxy_info *p, const bool force)
{
    /*
     * in case of forced (re)load, make sure the static storage is set as
     * undefined, otherwise get_user_pass() won't try to load any credential
     */
    if (force)
    {
        clear_user_pass_http();
    }

    if (!static_proxy_user_pass.defined)
    {
        unsigned int flags = GET_USER_PASS_MANAGEMENT;
        if (p->queried_creds)
        {
            flags |= GET_USER_PASS_PREVIOUS_CREDS_FAILED;
        }
        if (p->options.inline_creds)
        {
            flags |= GET_USER_PASS_INLINE_CREDS;
        }
        get_user_pass(&static_proxy_user_pass,
                      p->options.auth_file,
                      UP_TYPE_PROXY,
                      flags);
        p->queried_creds = true;
        p->up = static_proxy_user_pass;
    }
}