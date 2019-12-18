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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct nn_sha1 {int* buffer; int buffer_offset; int* state; scalar_t__ is_little_endian; } ;

/* Variables and functions */
 size_t SHA1_BLOCK_LEN ; 
 int sha1_rol32 (int,int) ; 

__attribute__((used)) static void nn_sha1_add (struct nn_sha1 *self, uint8_t data)
{
    uint8_t i;
    uint32_t a, b, c, d, e, t;
    uint8_t * const buf = (uint8_t*) self->buffer;

    if (self->is_little_endian)
        buf [self->buffer_offset ^ 3] = data;
    else
        buf [self->buffer_offset] = data;

    self->buffer_offset++;
    if (self->buffer_offset == SHA1_BLOCK_LEN) {
        a = self->state [0];
        b = self->state [1];
        c = self->state [2];
        d = self->state [3];
        e = self->state [4];
        for (i = 0; i < 80; i++) {
            if (i >= 16) {
                t = self->buffer [(i + 13) & 15] ^
                    self->buffer [(i + 8) & 15] ^
                    self->buffer [(i + 2) & 15] ^
                    self->buffer [i & 15];
                self->buffer [i & 15] = sha1_rol32 (t, 1);
            }

            if (i < 20)
                t = (d ^ (b & (c ^ d))) + 0x5A827999;
            else if (i < 40)
                t = (b ^ c ^ d) + 0x6ED9EBA1;
            else if (i < 60)
                t = ((b & c) | (d & (b | c))) + 0x8F1BBCDC;
            else
                t = (b ^ c ^ d) + 0xCA62C1D6;

            t += sha1_rol32 (a, 5) + e + self->buffer [i & 15];
            e = d;
            d = c;
            c = sha1_rol32 (b, 30);
            b = a;
            a = t;
        }

        self->state [0] += a;
        self->state [1] += b;
        self->state [2] += c;
        self->state [3] += d;
        self->state [4] += e;

        self->buffer_offset = 0;
    }
}