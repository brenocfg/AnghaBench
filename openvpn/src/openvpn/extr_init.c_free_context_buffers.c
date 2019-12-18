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
struct context_buffers {int /*<<< orphan*/  decrypt_buf; int /*<<< orphan*/  encrypt_buf; int /*<<< orphan*/  decompress_buf; int /*<<< orphan*/  compress_buf; int /*<<< orphan*/  aux_buf; int /*<<< orphan*/  read_tun_buf; int /*<<< orphan*/  read_link_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct context_buffers*) ; 
 int /*<<< orphan*/  free_buf (int /*<<< orphan*/ *) ; 

void
free_context_buffers(struct context_buffers *b)
{
    if (b)
    {
        free_buf(&b->read_link_buf);
        free_buf(&b->read_tun_buf);
        free_buf(&b->aux_buf);

#ifdef USE_COMP
        free_buf(&b->compress_buf);
        free_buf(&b->decompress_buf);
#endif

        free_buf(&b->encrypt_buf);
        free_buf(&b->decrypt_buf);

        free(b);
    }
}