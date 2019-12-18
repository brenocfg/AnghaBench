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
struct session {int /*<<< orphan*/  key; } ;
struct plugin {int dummy; } ;
struct openvpn_plugin_args_func_in {scalar_t__ per_client_context; scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_store (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovpn_note (char*,char*) ; 

__attribute__((used)) static void
client_store(struct openvpn_plugin_args_func_in const *args)
{
    struct plugin *plugin = (struct plugin  *)args->handle;
    struct session *sess  = (struct session *)args->per_client_context;

    char *file = "/tmp/openvpn_sso_user";
    ovpn_note("app session file: %s", file);
    file_store(file, sess->key);
}