#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tls_session {TYPE_3__* opt; struct key_state* key; } ;
struct TYPE_4__ {int /*<<< orphan*/  encrypt; } ;
struct TYPE_5__ {TYPE_1__ key_ctx_bi; } ;
struct key_state {TYPE_2__ crypto_options; } ;
struct key {int dummy; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_6__ {int key_method; int /*<<< orphan*/  key_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  D_TLS_ERRORS ; 
 size_t KS_PRIMARY ; 
 int /*<<< orphan*/  OPENVPN_OP_ENCRYPT ; 
 int buf_init (struct buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_write (struct buffer*,char const*,int const) ; 
 int /*<<< orphan*/  check_key (struct key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_key_random (struct key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_key_ctx (int /*<<< orphan*/ *,struct key*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* local_options_string (struct tls_session*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  secure_memzero (struct key*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  write_key (struct key*,int /*<<< orphan*/ *,struct buffer*) ; 

__attribute__((used)) static bool
key_method_1_write(struct buffer *buf, struct tls_session *session)
{
    struct key key;
    struct key_state *ks = &session->key[KS_PRIMARY];      /* primary key */

    ASSERT(session->opt->key_method == 1);
    ASSERT(buf_init(buf, 0));

    generate_key_random(&key, &session->opt->key_type);
    if (!check_key(&key, &session->opt->key_type))
    {
        msg(D_TLS_ERRORS, "TLS Error: Bad encrypting key generated");
        return false;
    }

    if (!write_key(&key, &session->opt->key_type, buf))
    {
        msg(D_TLS_ERRORS, "TLS Error: write_key failed");
        return false;
    }

    init_key_ctx(&ks->crypto_options.key_ctx_bi.encrypt, &key,
                 &session->opt->key_type, OPENVPN_OP_ENCRYPT,
                 "Data Channel Encrypt");
    secure_memzero(&key, sizeof(key));

    /* send local options string */
    {
        const char *local_options = local_options_string(session);
        const int optlen = strlen(local_options) + 1;
        if (!buf_write(buf, local_options, optlen))
        {
            msg(D_TLS_ERRORS, "TLS Error: KM1 write options failed");
            return false;
        }
    }

    return true;
}