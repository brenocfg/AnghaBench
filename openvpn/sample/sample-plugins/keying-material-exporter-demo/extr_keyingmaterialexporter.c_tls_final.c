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
struct session {int /*<<< orphan*/  user; int /*<<< orphan*/  key; } ;
struct plugin {int type; } ;
struct openvpn_plugin_args_func_return {int dummy; } ;
struct openvpn_plugin_args_func_in {int /*<<< orphan*/  envp; scalar_t__ per_client_context; scalar_t__ handle; } ;

/* Variables and functions */
#define  CLIENT 129 
 int OPENVPN_PLUGIN_FUNC_ERROR ; 
 int OPENVPN_PLUGIN_FUNC_SUCCESS ; 
#define  SERVER 128 
 int /*<<< orphan*/  client_store (struct openvpn_plugin_args_func_in const*) ; 
 char* get_env (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovpn_note (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_store (struct openvpn_plugin_args_func_in const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 

__attribute__((used)) static int
tls_final(struct openvpn_plugin_args_func_in const *args,
          struct openvpn_plugin_args_func_return *rv)
{
    struct plugin *plugin = (struct plugin  *)args->handle;
    struct session *sess  = (struct session *)args->per_client_context;

    const char *key;
    if (!(key = get_env("exported_keying_material", args->envp)))
    {
        return OPENVPN_PLUGIN_FUNC_ERROR;
    }

    snprintf(sess->key, sizeof(sess->key) - 1, "%s", key);
    ovpn_note("app session key:  %s", sess->key);

    switch (plugin->type)
    {
        case SERVER:
            server_store(args);
            break;

        case CLIENT:
            client_store(args);
            return OPENVPN_PLUGIN_FUNC_SUCCESS;
    }

    ovpn_note("app session user: %s", sess->user);
    return OPENVPN_PLUGIN_FUNC_SUCCESS;
}