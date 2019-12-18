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
struct tls_multi {struct key_state* save_ks; } ;
struct key_state {int /*<<< orphan*/  n_bytes; int /*<<< orphan*/  n_packets; } ;
struct buffer {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct key_state*) ; 

void
tls_post_encrypt(struct tls_multi *multi, struct buffer *buf)
{
    struct key_state *ks = multi->save_ks;
    multi->save_ks = NULL;

    if (buf->len > 0)
    {
        ASSERT(ks);

        ++ks->n_packets;
        ks->n_bytes += buf->len;
    }
}