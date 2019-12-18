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
struct key_type {int /*<<< orphan*/  digest; int /*<<< orphan*/  cipher; } ;
struct key_ctx {int dummy; } ;
struct key {int dummy; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  srv_key ;

/* Variables and functions */
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  buf_set_write (struct buffer*,void*,int) ; 
 int /*<<< orphan*/  init_key_ctx (struct key_ctx*,struct key*,struct key_type*,int,char*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  read_pem_key_file (struct buffer*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  secure_memzero (struct key*,int) ; 
 struct key_type tls_crypt_kt () ; 
 int /*<<< orphan*/  tls_crypt_v2_srv_pem_name ; 

void
tls_crypt_v2_init_server_key(struct key_ctx *key_ctx, bool encrypt,
                             const char *key_file, const char *key_inline)
{
    struct key srv_key;
    struct buffer srv_key_buf;

    buf_set_write(&srv_key_buf, (void *)&srv_key, sizeof(srv_key));
    if (!read_pem_key_file(&srv_key_buf, tls_crypt_v2_srv_pem_name,
                           key_file, key_inline))
    {
        msg(M_FATAL, "ERROR: invalid tls-crypt-v2 server key format");
    }

    struct key_type kt = tls_crypt_kt();
    if (!kt.cipher || !kt.digest)
    {
        msg(M_FATAL, "ERROR: --tls-crypt-v2 not supported");
    }
    init_key_ctx(key_ctx, &srv_key, &kt, encrypt, "tls-crypt-v2 server key");
    secure_memzero(&srv_key, sizeof(srv_key));
}