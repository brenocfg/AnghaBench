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
struct x509_track {int dummy; } ;
struct gc_arena {int dummy; } ;
struct env_set {int dummy; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  openvpn_x509_cert_t ;
typedef  int /*<<< orphan*/  envname ;

/* Variables and functions */
 int /*<<< orphan*/  BLEN (struct buffer*) ; 
 int /*<<< orphan*/  BPTR (struct buffer*) ; 
 char* backend_x509_get_serial (int /*<<< orphan*/ *,struct gc_arena*) ; 
 char* backend_x509_get_serial_hex (int /*<<< orphan*/ *,struct gc_arena*) ; 
 char* format_hex_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct gc_arena*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  openvpn_snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  setenv_str (struct env_set*,char*,char const*) ; 
 struct buffer x509_get_sha1_fingerprint (int /*<<< orphan*/ *,struct gc_arena*) ; 
 struct buffer x509_get_sha256_fingerprint (int /*<<< orphan*/ *,struct gc_arena*) ; 
 int /*<<< orphan*/  x509_setenv (struct env_set*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x509_setenv_track (struct x509_track const*,struct env_set*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
verify_cert_set_env(struct env_set *es, openvpn_x509_cert_t *peer_cert, int cert_depth,
                    const char *subject, const char *common_name,
                    const struct x509_track *x509_track)
{
    char envname[64];
    char *serial = NULL;
    struct gc_arena gc = gc_new();

    /* Save X509 fields in environment */
    if (x509_track)
    {
        x509_setenv_track(x509_track, es, cert_depth, peer_cert);
    }
    else
    {
        x509_setenv(es, cert_depth, peer_cert);
    }

    /* export subject name string as environmental variable */
    openvpn_snprintf(envname, sizeof(envname), "tls_id_%d", cert_depth);
    setenv_str(es, envname, subject);

#if 0
    /* export common name string as environmental variable */
    openvpn_snprintf(envname, sizeof(envname), "tls_common_name_%d", cert_depth);
    setenv_str(es, envname, common_name);
#endif

    /* export X509 cert fingerprints */
    {
        struct buffer sha1 = x509_get_sha1_fingerprint(peer_cert, &gc);
        struct buffer sha256 = x509_get_sha256_fingerprint(peer_cert, &gc);

        openvpn_snprintf(envname, sizeof(envname), "tls_digest_%d", cert_depth);
        setenv_str(es, envname,
                   format_hex_ex(BPTR(&sha1), BLEN(&sha1), 0, 1, ":", &gc));

        openvpn_snprintf(envname, sizeof(envname), "tls_digest_sha256_%d",
                         cert_depth);
        setenv_str(es, envname,
                   format_hex_ex(BPTR(&sha256), BLEN(&sha256), 0, 1, ":", &gc));
    }

    /* export serial number as environmental variable */
    serial = backend_x509_get_serial(peer_cert, &gc);
    openvpn_snprintf(envname, sizeof(envname), "tls_serial_%d", cert_depth);
    setenv_str(es, envname, serial);

    /* export serial number in hex as environmental variable */
    serial = backend_x509_get_serial_hex(peer_cert, &gc);
    openvpn_snprintf(envname, sizeof(envname), "tls_serial_hex_%d", cert_depth);
    setenv_str(es, envname, serial);

    gc_free(&gc);
}