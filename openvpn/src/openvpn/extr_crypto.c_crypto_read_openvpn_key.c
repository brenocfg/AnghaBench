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
struct key_type {int dummy; } ;
struct key_direction_state {int /*<<< orphan*/  need_keys; } ;
struct key_ctx_bi {int dummy; } ;
struct key2 {int n; } ;
typedef  int /*<<< orphan*/  key2 ;

/* Variables and functions */
 int /*<<< orphan*/  M_ERR ; 
 int RKF_INLINE ; 
 int RKF_MUST_SUCCEED ; 
 int /*<<< orphan*/  init_key_ctx_bi (struct key_ctx_bi*,struct key2*,int const,struct key_type const*,char const*) ; 
 int /*<<< orphan*/  key_direction_state_init (struct key_direction_state*,int const) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  must_have_n_keys (char const*,char const*,struct key2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_key_file (struct key2*,char const*,int) ; 
 int /*<<< orphan*/  secure_memzero (struct key2*,int) ; 
 int /*<<< orphan*/  verify_fix_key2 (struct key2*,struct key_type const*,char const*) ; 

void
crypto_read_openvpn_key(const struct key_type *key_type,
                        struct key_ctx_bi *ctx, const char *key_file, const char *key_inline,
                        const int key_direction, const char *key_name, const char *opt_name)
{
    struct key2 key2;
    struct key_direction_state kds;

    if (key_inline)
    {
        read_key_file(&key2, key_inline, RKF_MUST_SUCCEED|RKF_INLINE);
    }
    else
    {
        read_key_file(&key2, key_file, RKF_MUST_SUCCEED);
    }

    if (key2.n != 2)
    {
        msg(M_ERR, "File '%s' does not have OpenVPN Static Key format.  Using "
            "free-form passphrase file is not supported anymore.", key_file);
    }

    /* check for and fix highly unlikely key problems */
    verify_fix_key2(&key2, key_type, key_file);

    /* handle key direction */
    key_direction_state_init(&kds, key_direction);
    must_have_n_keys(key_file, opt_name, &key2, kds.need_keys);

    /* initialize key in both directions */
    init_key_ctx_bi(ctx, &key2, key_direction, key_type, key_name);
    secure_memzero(&key2, sizeof(key2));
}