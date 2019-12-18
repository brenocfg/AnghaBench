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
struct key_state {int /*<<< orphan*/  paybuf; int /*<<< orphan*/  ks_ssl; } ;
struct buffer {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 struct buffer* buffer_list_peek (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_list_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_state_write_plaintext_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flush_payload_buffer(struct key_state *ks)
{
    struct buffer *b;

    while ((b = buffer_list_peek(ks->paybuf)))
    {
        key_state_write_plaintext_const(&ks->ks_ssl, b->data, b->len);
        buffer_list_pop(ks->paybuf);
    }
}