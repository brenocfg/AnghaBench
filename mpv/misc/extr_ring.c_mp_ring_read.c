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
struct mp_ring {int /*<<< orphan*/  rpos; scalar_t__ buffer; } ;

/* Variables and functions */
 int MPMIN (int,int) ; 
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,int) ; 
 int mp_ring_buffered (struct mp_ring*) ; 
 int mp_ring_get_rpos (struct mp_ring*) ; 
 int mp_ring_size (struct mp_ring*) ; 

int mp_ring_read(struct mp_ring *buffer, unsigned char *dest, int len)
{
    int size     = mp_ring_size(buffer);
    int buffered = mp_ring_buffered(buffer);
    int read_len = MPMIN(len, buffered);
    int read_ptr = mp_ring_get_rpos(buffer) % size;

    int len1 = MPMIN(size - read_ptr, read_len);
    int len2 = read_len - len1;

    if (dest) {
        memcpy(dest, buffer->buffer + read_ptr, len1);
        memcpy(dest + len1, buffer->buffer, len2);
    }

    atomic_fetch_add(&buffer->rpos, read_len);

    return read_len;
}