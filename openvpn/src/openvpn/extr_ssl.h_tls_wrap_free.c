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
struct TYPE_2__ {int /*<<< orphan*/  key_ctx_bi; int /*<<< orphan*/  packet_id; } ;
struct tls_wrap_ctx {int /*<<< orphan*/  work; int /*<<< orphan*/  tls_crypt_v2_metadata; TYPE_1__ opt; scalar_t__ cleanup_key_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_key_ctx_bi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_id_free (int /*<<< orphan*/ *) ; 
 scalar_t__ packet_id_initialized (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
tls_wrap_free(struct tls_wrap_ctx *tls_wrap)
{
    if (packet_id_initialized(&tls_wrap->opt.packet_id))
    {
        packet_id_free(&tls_wrap->opt.packet_id);
    }

    if (tls_wrap->cleanup_key_ctx)
    {
        free_key_ctx_bi(&tls_wrap->opt.key_ctx_bi);
    }

    free_buf(&tls_wrap->tls_crypt_v2_metadata);
    free_buf(&tls_wrap->work);
}