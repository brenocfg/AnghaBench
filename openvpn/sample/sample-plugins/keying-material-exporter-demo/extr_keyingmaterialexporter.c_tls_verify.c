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
struct session {int dummy; } ;
struct plugin {scalar_t__ type; } ;
struct openvpn_plugin_args_func_in {int /*<<< orphan*/  current_cert; scalar_t__ per_client_context; scalar_t__ handle; } ;

/* Variables and functions */
 int OPENVPN_PLUGIN_FUNC_ERROR ; 
 int OPENVPN_PLUGIN_FUNC_SUCCESS ; 
 scalar_t__ SERVER ; 
 int /*<<< orphan*/  ovpn_err (char*) ; 
 int /*<<< orphan*/  session_user_set (struct session*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tls_verify(struct openvpn_plugin_args_func_in const *args)
{
    struct plugin *plugin = (struct plugin  *)args->handle;
    struct session *sess  = (struct session *)args->per_client_context;

    /* we store cert subject for the server end point only */
    if (plugin->type != SERVER)
    {
        return OPENVPN_PLUGIN_FUNC_SUCCESS;
    }

    if (!args->current_cert)
    {
        ovpn_err("this example plugin requires client certificate");
        return OPENVPN_PLUGIN_FUNC_ERROR;
    }

    session_user_set(sess, args->current_cert);

    return OPENVPN_PLUGIN_FUNC_SUCCESS;
}