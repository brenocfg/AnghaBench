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
struct gc_arena {int dummy; } ;
struct env_set {int dummy; } ;
struct argv {int dummy; } ;
typedef  int /*<<< orphan*/  result_t ;
typedef  int /*<<< orphan*/  openvpn_x509_cert_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_HANDSHAKE ; 
 int /*<<< orphan*/  D_TLS_DEBUG ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  argv_msg_prefix (int /*<<< orphan*/ ,struct argv*,char*) ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_parse_cmd (struct argv*,char const*) ; 
 int /*<<< orphan*/  argv_printf_cat (struct argv*,char*,int,char*) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int,char*) ; 
 int openvpn_run_script (struct argv*,struct env_set*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_unlink (char const*) ; 
 int /*<<< orphan*/  setenv_str (struct env_set*,char*,char const*) ; 
 char* verify_cert_export_cert (int /*<<< orphan*/ *,char const*,struct gc_arena*) ; 

__attribute__((used)) static result_t
verify_cert_call_command(const char *verify_command, struct env_set *es,
                         int cert_depth, openvpn_x509_cert_t *cert, char *subject, const char *verify_export_cert)
{
    const char *tmp_file = NULL;
    int ret;
    struct gc_arena gc = gc_new();
    struct argv argv = argv_new();

    setenv_str(es, "script_type", "tls-verify");

    if (verify_export_cert)
    {
        tmp_file = verify_cert_export_cert(cert, verify_export_cert, &gc);
        if (!tmp_file)
        {
            ret = false;
            goto cleanup;
        }
        setenv_str(es, "peer_cert", tmp_file);
    }

    argv_parse_cmd(&argv, verify_command);
    argv_printf_cat(&argv, "%d %s", cert_depth, subject);

    argv_msg_prefix(D_TLS_DEBUG, &argv, "TLS: executing verify command");
    ret = openvpn_run_script(&argv, es, 0, "--tls-verify script");

    if (verify_export_cert)
    {
        if (tmp_file)
        {
            platform_unlink(tmp_file);
        }
    }

cleanup:
    gc_free(&gc);
    argv_reset(&argv);

    if (ret)
    {
        msg(D_HANDSHAKE, "VERIFY SCRIPT OK: depth=%d, %s",
            cert_depth, subject);
        return SUCCESS;
    }

    msg(D_HANDSHAKE, "VERIFY SCRIPT ERROR: depth=%d, %s",
        cert_depth, subject);
    return FAILURE;             /* Reject connection */
}