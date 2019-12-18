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
struct options {int management_flags; int ssl_flags; int /*<<< orphan*/  tmp_dir; int /*<<< orphan*/  chroot_dir; int /*<<< orphan*/  client_config_dir; int /*<<< orphan*/  tls_export_cert; int /*<<< orphan*/  status_file; int /*<<< orphan*/  writepid; int /*<<< orphan*/  auth_user_pass_file; int /*<<< orphan*/  management_user_pass; int /*<<< orphan*/  key_pass_file; int /*<<< orphan*/  packet_id_file; int /*<<< orphan*/  shared_secret_file; int /*<<< orphan*/  genkey_filename; TYPE_1__* connection_list; int /*<<< orphan*/  crl_file; int /*<<< orphan*/  pkcs12_file; int /*<<< orphan*/  priv_key_file; int /*<<< orphan*/  extra_certs_file; int /*<<< orphan*/  cert_file; int /*<<< orphan*/  ca_path; int /*<<< orphan*/  ca_file; int /*<<< orphan*/  dh_file; } ;
struct connection_entry {int /*<<< orphan*/  tls_crypt_v2_file; int /*<<< orphan*/  tls_crypt_file; int /*<<< orphan*/  tls_auth_file; } ;
struct TYPE_2__ {int len; struct connection_entry** array; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 int CHKACC_ACPTSTDIN ; 
 int CHKACC_DIRPATH ; 
 int CHKACC_FILE ; 
 int CHKACC_FILEXSTWR ; 
 int CHKACC_INLINE ; 
 int CHKACC_PRIVATE ; 
 int MF_EXTERNAL_KEY ; 
 int /*<<< orphan*/  M_USAGE ; 
 int R_OK ; 
 int SSLF_CRL_VERIFY_DIR ; 
 int W_OK ; 
 int X_OK ; 
 int check_file_access (int,int /*<<< orphan*/ ,int,char*) ; 
 int check_file_access_chroot (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
options_postprocess_filechecks(struct options *options)
{
    bool errs = false;

    /* ** SSL/TLS/crypto related files ** */
    errs |= check_file_access(CHKACC_FILE|CHKACC_INLINE, options->dh_file, R_OK, "--dh");
    errs |= check_file_access(CHKACC_FILE|CHKACC_INLINE, options->ca_file, R_OK, "--ca");
    errs |= check_file_access_chroot(options->chroot_dir, CHKACC_FILE, options->ca_path, R_OK, "--capath");
    errs |= check_file_access(CHKACC_FILE|CHKACC_INLINE, options->cert_file, R_OK, "--cert");
    errs |= check_file_access(CHKACC_FILE|CHKACC_INLINE, options->extra_certs_file, R_OK,
                              "--extra-certs");
#ifdef ENABLE_MANAGEMENT
    if (!(options->management_flags & MF_EXTERNAL_KEY))
#endif
    {
        errs |= check_file_access(CHKACC_FILE|CHKACC_INLINE|CHKACC_PRIVATE,
                                  options->priv_key_file, R_OK, "--key");
    }
    errs |= check_file_access(CHKACC_FILE|CHKACC_INLINE|CHKACC_PRIVATE,
                              options->pkcs12_file, R_OK, "--pkcs12");

    if (options->ssl_flags & SSLF_CRL_VERIFY_DIR)
    {
        errs |= check_file_access_chroot(options->chroot_dir, CHKACC_FILE, options->crl_file, R_OK|X_OK,
                                         "--crl-verify directory");
    }
    else
    {
        errs |= check_file_access_chroot(options->chroot_dir, CHKACC_FILE|CHKACC_INLINE,
                                         options->crl_file, R_OK, "--crl-verify");
    }

    ASSERT(options->connection_list);
    for (int i = 0; i < options->connection_list->len; ++i)
    {
        struct connection_entry *ce = options->connection_list->array[i];

        errs |= check_file_access(CHKACC_FILE|CHKACC_INLINE|CHKACC_PRIVATE,
                                  ce->tls_auth_file, R_OK, "--tls-auth");

        errs |= check_file_access(CHKACC_FILE|CHKACC_INLINE|CHKACC_PRIVATE,
                                  ce->tls_crypt_file, R_OK, "--tls-crypt");

        errs |= check_file_access(CHKACC_FILE|CHKACC_INLINE|CHKACC_PRIVATE,
                                  ce->tls_crypt_v2_file, R_OK,
                                  "--tls-crypt-v2");
    }

    errs |= check_file_access(CHKACC_FILE|CHKACC_INLINE|CHKACC_PRIVATE,
                              options->genkey_filename, R_OK,
                              "--genkey");
    errs |= check_file_access(CHKACC_FILE|CHKACC_INLINE|CHKACC_PRIVATE,
                              options->shared_secret_file, R_OK, "--secret");

    errs |= check_file_access(CHKACC_DIRPATH|CHKACC_FILEXSTWR,
                              options->packet_id_file, R_OK|W_OK, "--replay-persist");

    /* ** Password files ** */
    errs |= check_file_access(CHKACC_FILE|CHKACC_ACPTSTDIN|CHKACC_PRIVATE,
                              options->key_pass_file, R_OK, "--askpass");
#ifdef ENABLE_MANAGEMENT
    errs |= check_file_access(CHKACC_FILE|CHKACC_ACPTSTDIN|CHKACC_PRIVATE,
                              options->management_user_pass, R_OK,
                              "--management user/password file");
#endif /* ENABLE_MANAGEMENT */
#if P2MP
    errs |= check_file_access(CHKACC_FILE|CHKACC_ACPTSTDIN|CHKACC_PRIVATE,
                              options->auth_user_pass_file, R_OK,
                              "--auth-user-pass");
#endif /* P2MP */

    /* ** System related ** */
    errs |= check_file_access(CHKACC_FILE, options->chroot_dir,
                              R_OK|X_OK, "--chroot directory");
    errs |= check_file_access(CHKACC_DIRPATH|CHKACC_FILEXSTWR, options->writepid,
                              R_OK|W_OK, "--writepid");

    /* ** Log related ** */
    errs |= check_file_access(CHKACC_DIRPATH|CHKACC_FILEXSTWR, options->status_file,
                              R_OK|W_OK, "--status");

    /* ** Config related ** */
    errs |= check_file_access_chroot(options->chroot_dir, CHKACC_FILE, options->tls_export_cert,
                                     R_OK|W_OK|X_OK, "--tls-export-cert");
#if P2MP_SERVER
    errs |= check_file_access_chroot(options->chroot_dir, CHKACC_FILE, options->client_config_dir,
                                     R_OK|X_OK, "--client-config-dir");
    errs |= check_file_access_chroot(options->chroot_dir, CHKACC_FILE, options->tmp_dir,
                                     R_OK|W_OK|X_OK, "Temporary directory (--tmp-dir)");

#endif /* P2MP_SERVER */

    if (errs)
    {
        msg(M_USAGE, "Please correct these errors.");
    }
}