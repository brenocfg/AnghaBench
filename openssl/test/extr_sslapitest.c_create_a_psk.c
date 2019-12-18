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
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  const SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CIPHER ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/ * SSL_CIPHER_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * SSL_SESSION_new () ; 
 int /*<<< orphan*/  SSL_SESSION_set1_master_key (int /*<<< orphan*/  const*,unsigned char const*,int) ; 
 int /*<<< orphan*/  SSL_SESSION_set_cipher (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSL_SESSION_set_protocol_version (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS13_AES_256_GCM_SHA384_BYTES ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 

__attribute__((used)) static SSL_SESSION *create_a_psk(SSL *ssl)
{
    const SSL_CIPHER *cipher = NULL;
    const unsigned char key[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
        0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
        0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b,
        0x2c, 0x2d, 0x2e, 0x2f
    };
    SSL_SESSION *sess = NULL;

    cipher = SSL_CIPHER_find(ssl, TLS13_AES_256_GCM_SHA384_BYTES);
    sess = SSL_SESSION_new();
    if (!TEST_ptr(sess)
            || !TEST_ptr(cipher)
            || !TEST_true(SSL_SESSION_set1_master_key(sess, key,
                                                      sizeof(key)))
            || !TEST_true(SSL_SESSION_set_cipher(sess, cipher))
            || !TEST_true(
                    SSL_SESSION_set_protocol_version(sess,
                                                     TLS1_3_VERSION))) {
        SSL_SESSION_free(sess);
        return NULL;
    }
    return sess;
}