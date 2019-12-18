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
typedef  int /*<<< orphan*/  uint8_t ;
struct nn_sha1 {int buffer_offset; int bytes_hashed; int* state; scalar_t__ is_little_endian; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_sha1_add (struct nn_sha1*,int) ; 

uint8_t* nn_sha1_result (struct nn_sha1 *self)
{
    int i;

    /*  Pad to complete the last block. */
    nn_sha1_add (self, 0x80);

    while (self->buffer_offset != 56)
        nn_sha1_add (self, 0x00);

    /*  Append length in the last 8 bytes. SHA-1 supports 64-bit hashes, so
        zero-pad the top bits. Shifting to multiply by 8 as SHA-1 supports
        bit- as well as byte-streams. */
    nn_sha1_add (self, 0);
    nn_sha1_add (self, 0);
    nn_sha1_add (self, 0);
    nn_sha1_add (self, self->bytes_hashed >> 29);
    nn_sha1_add (self, self->bytes_hashed >> 21);
    nn_sha1_add (self, self->bytes_hashed >> 13);
    nn_sha1_add (self, self->bytes_hashed >> 5);
    nn_sha1_add (self, self->bytes_hashed << 3);

    /*  Correct byte order for little-endian systems. */
    if (self->is_little_endian) {
        for (i = 0; i < 5; i++) {
            self->state [i] =
                (((self->state [i]) << 24) & 0xFF000000) |
                (((self->state [i]) << 8) & 0x00FF0000) |
                (((self->state [i]) >> 8) & 0x0000FF00) |
                (((self->state [i]) >> 24) & 0x000000FF);
        }
    }

    /* 20-octet pointer to hash. */
    return (uint8_t*) self->state;
}