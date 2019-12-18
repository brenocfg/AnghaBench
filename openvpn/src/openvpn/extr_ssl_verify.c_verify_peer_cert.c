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
struct tls_options {scalar_t__ ns_cert_type; scalar_t__* remote_cert_ku; scalar_t__ verify_x509_type; int /*<<< orphan*/  verify_x509_name; int /*<<< orphan*/ * remote_cert_eku; } ;
typedef  scalar_t__ result_t ;
typedef  int /*<<< orphan*/  openvpn_x509_cert_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_HANDSHAKE ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  MAX_PARMS ; 
 scalar_t__ NS_CERT_CHECK_NONE ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ VERIFY_X509_NONE ; 
 scalar_t__ VERIFY_X509_SUBJECT_DN ; 
 scalar_t__ VERIFY_X509_SUBJECT_RDN ; 
 scalar_t__ VERIFY_X509_SUBJECT_RDN_PREFIX ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_nsCertType (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ x509_verify_cert_eku (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ x509_verify_cert_ku (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ x509_verify_ns_cert_type (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static result_t
verify_peer_cert(const struct tls_options *opt, openvpn_x509_cert_t *peer_cert,
                 const char *subject, const char *common_name)
{
    /* verify certificate nsCertType */
    if (opt->ns_cert_type != NS_CERT_CHECK_NONE)
    {
        if (SUCCESS == x509_verify_ns_cert_type(peer_cert, opt->ns_cert_type))
        {
            msg(D_HANDSHAKE, "VERIFY OK: nsCertType=%s",
                print_nsCertType(opt->ns_cert_type));
        }
        else
        {
            msg(D_HANDSHAKE, "VERIFY nsCertType ERROR: %s, require nsCertType=%s",
                subject, print_nsCertType(opt->ns_cert_type));
            return FAILURE;             /* Reject connection */
        }
    }

    /* verify certificate ku */
    if (opt->remote_cert_ku[0] != 0)
    {
        if (SUCCESS == x509_verify_cert_ku(peer_cert, opt->remote_cert_ku, MAX_PARMS))
        {
            msg(D_HANDSHAKE, "VERIFY KU OK");
        }
        else
        {
            msg(D_HANDSHAKE, "VERIFY KU ERROR");
            return FAILURE;             /* Reject connection */
        }
    }

    /* verify certificate eku */
    if (opt->remote_cert_eku != NULL)
    {
        if (SUCCESS == x509_verify_cert_eku(peer_cert, opt->remote_cert_eku))
        {
            msg(D_HANDSHAKE, "VERIFY EKU OK");
        }
        else
        {
            msg(D_HANDSHAKE, "VERIFY EKU ERROR");
            return FAILURE;             /* Reject connection */
        }
    }

    /* verify X509 name or username against --verify-x509-[user]name */
    if (opt->verify_x509_type != VERIFY_X509_NONE)
    {
        if ( (opt->verify_x509_type == VERIFY_X509_SUBJECT_DN
              && strcmp(opt->verify_x509_name, subject) == 0)
             || (opt->verify_x509_type == VERIFY_X509_SUBJECT_RDN
                 && strcmp(opt->verify_x509_name, common_name) == 0)
             || (opt->verify_x509_type == VERIFY_X509_SUBJECT_RDN_PREFIX
                 && strncmp(opt->verify_x509_name, common_name,
                            strlen(opt->verify_x509_name)) == 0) )
        {
            msg(D_HANDSHAKE, "VERIFY X509NAME OK: %s", subject);
        }
        else
        {
            msg(D_HANDSHAKE, "VERIFY X509NAME ERROR: %s, must be %s",
                subject, opt->verify_x509_name);
            return FAILURE;             /* Reject connection */
        }
    }

    return SUCCESS;
}