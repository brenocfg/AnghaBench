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
struct key_schedule {int /*<<< orphan*/  tls_crypt_v2_server_key; int /*<<< orphan*/  ssl_ctx; int /*<<< orphan*/  static_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct key_schedule) ; 
 int /*<<< orphan*/  free_key_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_key_ctx_bi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_ctx_free (int /*<<< orphan*/ *) ; 
 scalar_t__ tls_ctx_initialised (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
key_schedule_free(struct key_schedule *ks, bool free_ssl_ctx)
{
    free_key_ctx_bi(&ks->static_key);
    if (tls_ctx_initialised(&ks->ssl_ctx) && free_ssl_ctx)
    {
        tls_ctx_free(&ks->ssl_ctx);
        free_key_ctx(&ks->tls_crypt_v2_server_key);
    }
    CLEAR(*ks);
}