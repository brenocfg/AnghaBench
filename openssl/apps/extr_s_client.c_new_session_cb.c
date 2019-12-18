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
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PEM_write_bio_SSL_SESSION (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_SESSION_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_version (int /*<<< orphan*/ *) ; 
 scalar_t__ TLS1_3_VERSION ; 
 int /*<<< orphan*/  bio_c_out ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * sess_out ; 

__attribute__((used)) static int new_session_cb(SSL *s, SSL_SESSION *sess)
{

    if (sess_out != NULL) {
        BIO *stmp = BIO_new_file(sess_out, "w");

        if (stmp == NULL) {
            BIO_printf(bio_err, "Error writing session file %s\n", sess_out);
        } else {
            PEM_write_bio_SSL_SESSION(stmp, sess);
            BIO_free(stmp);
        }
    }

    /*
     * Session data gets dumped on connection for TLSv1.2 and below, and on
     * arrival of the NewSessionTicket for TLSv1.3.
     */
    if (SSL_version(s) == TLS1_3_VERSION) {
        BIO_printf(bio_c_out,
                   "---\nPost-Handshake New Session Ticket arrived:\n");
        SSL_SESSION_print(bio_c_out, sess);
        BIO_printf(bio_c_out, "---\n");
    }

    /*
     * We always return a "fail" response so that the session gets freed again
     * because we haven't used the reference.
     */
    return 0;
}