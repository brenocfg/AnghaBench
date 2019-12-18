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
struct plugin_list {int dummy; } ;
struct env_set {int dummy; } ;
struct argv {int dummy; } ;
typedef  int /*<<< orphan*/  result_t ;
typedef  int /*<<< orphan*/  openvpn_x509_cert_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_HANDSHAKE ; 
 int /*<<< orphan*/  FAILURE ; 
 int OPENVPN_PLUGIN_FUNC_SUCCESS ; 
 int /*<<< orphan*/  OPENVPN_PLUGIN_TLS_VERIFY ; 
 int /*<<< orphan*/  SUCCESS ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_printf (struct argv*,char*,int,char*) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int,char*) ; 
 int plugin_call_ssl (struct plugin_list const*,int /*<<< orphan*/ ,struct argv*,int /*<<< orphan*/ *,struct env_set*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ plugin_defined (struct plugin_list const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static result_t
verify_cert_call_plugin(const struct plugin_list *plugins, struct env_set *es,
                        int cert_depth, openvpn_x509_cert_t *cert, char *subject)
{
    if (plugin_defined(plugins, OPENVPN_PLUGIN_TLS_VERIFY))
    {
        int ret;
        struct argv argv = argv_new();

        argv_printf(&argv, "%d %s", cert_depth, subject);

        ret = plugin_call_ssl(plugins, OPENVPN_PLUGIN_TLS_VERIFY, &argv, NULL, es, cert_depth, cert);

        argv_reset(&argv);

        if (ret == OPENVPN_PLUGIN_FUNC_SUCCESS)
        {
            msg(D_HANDSHAKE, "VERIFY PLUGIN OK: depth=%d, %s",
                cert_depth, subject);
        }
        else
        {
            msg(D_HANDSHAKE, "VERIFY PLUGIN ERROR: depth=%d, %s",
                cert_depth, subject);
            return FAILURE;             /* Reject connection */
        }
    }
    return SUCCESS;
}