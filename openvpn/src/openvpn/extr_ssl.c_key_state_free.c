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
struct TYPE_2__ {int /*<<< orphan*/  packet_id; int /*<<< orphan*/  key_ctx_bi; } ;
struct key_state {TYPE_1__ crypto_options; scalar_t__ key_src; scalar_t__ rec_ack; scalar_t__ rec_reliable; scalar_t__ send_reliable; int /*<<< orphan*/  paybuf; int /*<<< orphan*/  ack_write_buf; int /*<<< orphan*/  plaintext_write_buf; int /*<<< orphan*/  plaintext_read_buf; int /*<<< orphan*/  ks_ssl; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_UNDEF ; 
 int /*<<< orphan*/  buffer_list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  free_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_key_ctx_bi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_state_rm_auth_control_file (struct key_state*) ; 
 int /*<<< orphan*/  key_state_ssl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_id_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reliable_free (scalar_t__) ; 
 int /*<<< orphan*/  secure_memzero (struct key_state*,int) ; 

__attribute__((used)) static void
key_state_free(struct key_state *ks, bool clear)
{
    ks->state = S_UNDEF;

    key_state_ssl_free(&ks->ks_ssl);

    free_key_ctx_bi(&ks->crypto_options.key_ctx_bi);
    free_buf(&ks->plaintext_read_buf);
    free_buf(&ks->plaintext_write_buf);
    free_buf(&ks->ack_write_buf);
    buffer_list_free(ks->paybuf);

    if (ks->send_reliable)
    {
        reliable_free(ks->send_reliable);
        free(ks->send_reliable);
    }

    if (ks->rec_reliable)
    {
        reliable_free(ks->rec_reliable);
        free(ks->rec_reliable);
    }

    if (ks->rec_ack)
    {
        free(ks->rec_ack);
    }

    if (ks->key_src)
    {
        free(ks->key_src);
    }

    packet_id_free(&ks->crypto_options.packet_id);

#ifdef PLUGIN_DEF_AUTH
    key_state_rm_auth_control_file(ks);
#endif

    if (clear)
    {
        secure_memzero(ks, sizeof(*ks));
    }
}