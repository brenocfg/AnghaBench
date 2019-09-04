#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {long compressed_len; int last_eob_len; int bi_valid; } ;
typedef  TYPE_1__ deflate_state ;

/* Variables and functions */
 int /*<<< orphan*/  END_BLOCK ; 
 int STATIC_TREES ; 
 int /*<<< orphan*/  bi_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  send_bits (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  send_code (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_ltree ; 

void zlib_tr_align(
	deflate_state *s
)
{
    send_bits(s, STATIC_TREES<<1, 3);
    send_code(s, END_BLOCK, static_ltree);
    s->compressed_len += 10L; /* 3 for block type, 7 for EOB */
    bi_flush(s);
    /* Of the 10 bits for the empty block, we have already sent
     * (10 - bi_valid) bits. The lookahead for the last real code (before
     * the EOB of the previous block) was thus at least one plus the length
     * of the EOB plus what we have just sent of the empty static block.
     */
    if (1 + s->last_eob_len + 10 - s->bi_valid < 9) {
        send_bits(s, STATIC_TREES<<1, 3);
        send_code(s, END_BLOCK, static_ltree);
        s->compressed_len += 10L;
        bi_flush(s);
    }
    s->last_eob_len = 7;
}