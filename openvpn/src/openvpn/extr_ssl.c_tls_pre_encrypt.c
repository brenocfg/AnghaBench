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
struct tls_multi {struct key_state* save_ks; struct key_state** key_scan; } ;
struct TYPE_2__ {scalar_t__ initialized; } ;
struct crypto_options {TYPE_1__ key_ctx_bi; } ;
struct key_state {scalar_t__ state; scalar_t__ auth_deferred_expire; int /*<<< orphan*/  key_id; struct crypto_options crypto_options; int /*<<< orphan*/  auth_deferred; scalar_t__ authenticated; } ;
struct gc_arena {int dummy; } ;
struct buffer {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TLS_KEYSELECT ; 
 int KEY_SCAN_SIZE ; 
 scalar_t__ S_ACTIVE ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 scalar_t__ now ; 
 int /*<<< orphan*/  print_key_id (struct tls_multi*,struct gc_arena*) ; 

void
tls_pre_encrypt(struct tls_multi *multi,
                struct buffer *buf, struct crypto_options **opt)
{
    multi->save_ks = NULL;
    if (buf->len > 0)
    {
        int i;
        struct key_state *ks_select = NULL;
        for (i = 0; i < KEY_SCAN_SIZE; ++i)
        {
            struct key_state *ks = multi->key_scan[i];
            if (ks->state >= S_ACTIVE
                && ks->authenticated
                && ks->crypto_options.key_ctx_bi.initialized
#ifdef ENABLE_DEF_AUTH
                && !ks->auth_deferred
#endif
                )
            {
                if (!ks_select)
                {
                    ks_select = ks;
                }
                if (now >= ks->auth_deferred_expire)
                {
                    ks_select = ks;
                    break;
                }
            }
        }

        if (ks_select)
        {
            *opt = &ks_select->crypto_options;
            multi->save_ks = ks_select;
            dmsg(D_TLS_KEYSELECT, "TLS: tls_pre_encrypt: key_id=%d", ks_select->key_id);
            return;
        }
        else
        {
            struct gc_arena gc = gc_new();
            dmsg(D_TLS_KEYSELECT, "TLS Warning: no data channel send key available: %s",
                 print_key_id(multi, &gc));
            gc_free(&gc);
        }
    }

    buf->len = 0;
    *opt = NULL;
}