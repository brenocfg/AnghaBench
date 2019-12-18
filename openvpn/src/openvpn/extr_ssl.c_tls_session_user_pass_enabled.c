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
struct tls_session {TYPE_1__* opt; } ;
struct TYPE_2__ {int /*<<< orphan*/  plugins; scalar_t__ auth_user_pass_verify_script; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPENVPN_PLUGIN_AUTH_USER_PASS_VERIFY ; 
 int /*<<< orphan*/  management ; 
 scalar_t__ management_enable_def_auth (int /*<<< orphan*/ ) ; 
 scalar_t__ plugin_defined (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
tls_session_user_pass_enabled(struct tls_session *session)
{
    return (session->opt->auth_user_pass_verify_script
            || plugin_defined(session->opt->plugins, OPENVPN_PLUGIN_AUTH_USER_PASS_VERIFY)
#ifdef MANAGEMENT_DEF_AUTH
            || management_enable_def_auth(management)
#endif
            );
}