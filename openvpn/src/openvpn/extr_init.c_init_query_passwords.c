#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ auth_user_pass_file; int /*<<< orphan*/  sc_info; scalar_t__ key_pass_file; } ;
struct context {TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_user_pass_setup (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pem_password_setup (scalar_t__) ; 

void
init_query_passwords(const struct context *c)
{
    /* Certificate password input */
    if (c->options.key_pass_file)
    {
        pem_password_setup(c->options.key_pass_file);
    }

#if P2MP
    /* Auth user/pass input */
    if (c->options.auth_user_pass_file)
    {
#ifdef ENABLE_MANAGEMENT
        auth_user_pass_setup(c->options.auth_user_pass_file, &c->options.sc_info);
#else
        auth_user_pass_setup(c->options.auth_user_pass_file, NULL);
#endif
    }
#endif
}