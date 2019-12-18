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
struct tls_session {TYPE_3__* opt; int /*<<< orphan*/  verified; struct key_state* key; } ;
struct TYPE_4__ {int /*<<< orphan*/  decrypt; } ;
struct TYPE_5__ {TYPE_1__ key_ctx_bi; } ;
struct key_state {int authenticated; TYPE_2__ crypto_options; } ;
struct key {int dummy; } ;
struct buffer {int len; } ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_6__ {int key_method; int /*<<< orphan*/  key_type; int /*<<< orphan*/  remote_options; int /*<<< orphan*/  disable_occ; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BPTR (struct buffer*) ; 
 int /*<<< orphan*/  D_TLS_ERRORS ; 
 size_t KS_PRIMARY ; 
 int /*<<< orphan*/  OPENVPN_OP_DECRYPT ; 
 int /*<<< orphan*/  buf_clear (struct buffer*) ; 
 int /*<<< orphan*/  check_key (struct key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_key_ctx (int /*<<< orphan*/ *,struct key*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  options_cmp_equal_safe (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  options_warning_safe (char*,int /*<<< orphan*/ ,int) ; 
 int read_key (struct key*,int /*<<< orphan*/ *,struct buffer*) ; 
 int /*<<< orphan*/  secure_memzero (struct key*,int) ; 

__attribute__((used)) static bool
key_method_1_read(struct buffer *buf, struct tls_session *session)
{
    int status;
    struct key key;
    struct key_state *ks = &session->key[KS_PRIMARY];      /* primary key */

    ASSERT(session->opt->key_method == 1);

    if (!session->verified)
    {
        msg(D_TLS_ERRORS,
            "TLS Error: Certificate verification failed (key-method 1)");
        goto error;
    }

    status = read_key(&key, &session->opt->key_type, buf);
    if (status != 1)
    {
        msg(D_TLS_ERRORS,
            "TLS Error: Error reading data channel key from plaintext buffer");
        goto error;
    }

    if (!check_key(&key, &session->opt->key_type))
    {
        msg(D_TLS_ERRORS, "TLS Error: Bad decrypting key received from peer");
        goto error;
    }

    if (buf->len < 1)
    {
        msg(D_TLS_ERRORS, "TLS Error: Missing options string");
        goto error;
    }

#ifdef ENABLE_OCC
    /* compare received remote options string
     * with our locally computed options string */
    if (!session->opt->disable_occ
        && !options_cmp_equal_safe((char *) BPTR(buf), session->opt->remote_options, buf->len))
    {
        options_warning_safe((char *) BPTR(buf), session->opt->remote_options, buf->len);
    }
#endif

    buf_clear(buf);

    init_key_ctx(&ks->crypto_options.key_ctx_bi.decrypt, &key,
                 &session->opt->key_type, OPENVPN_OP_DECRYPT,
                 "Data Channel Decrypt");
    secure_memzero(&key, sizeof(key));
    ks->authenticated = true;
    return true;

error:
    buf_clear(buf);
    secure_memzero(&key, sizeof(key));
    return false;
}