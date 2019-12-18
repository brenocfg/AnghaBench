#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_8__ {int rounds; TYPE_1__* rd_key; } ;
struct TYPE_7__ {void** u; } ;
typedef  TYPE_1__ ARIA_u128 ;
typedef  TYPE_2__ ARIA_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  ARIA_BLOCK_SIZE ; 
 int /*<<< orphan*/  ARIA_DEC_DIFF_BYTE (void*,void*,void*,void*) ; 
 int /*<<< orphan*/  ARIA_DIFF_BYTE (void*,void*,void*,void*) ; 
 int /*<<< orphan*/  ARIA_DIFF_WORD (void*,void*,void*,void*) ; 
 int aria_set_encrypt_key (unsigned char const*,int const,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

int aria_set_decrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key)
{
    ARIA_u128 *rk_head;
    ARIA_u128 *rk_tail;
    register uint32_t w1, w2;
    register uint32_t reg0, reg1, reg2, reg3;
    uint32_t s0, s1, s2, s3;

    const int r = aria_set_encrypt_key(userKey, bits, key);

    if (r != 0) {
        return r;
    }

    rk_head = key->rd_key;
    rk_tail = rk_head + key->rounds;

    reg0 = rk_head->u[0];
    reg1 = rk_head->u[1];
    reg2 = rk_head->u[2];
    reg3 = rk_head->u[3];

    memcpy(rk_head, rk_tail, ARIA_BLOCK_SIZE);

    rk_tail->u[0] = reg0;
    rk_tail->u[1] = reg1;
    rk_tail->u[2] = reg2;
    rk_tail->u[3] = reg3;

    rk_head++;
    rk_tail--;

    for (; rk_head < rk_tail; rk_head++, rk_tail--) {
        ARIA_DEC_DIFF_BYTE(rk_head->u[0], reg0, w1, w2);
        ARIA_DEC_DIFF_BYTE(rk_head->u[1], reg1, w1, w2);
        ARIA_DEC_DIFF_BYTE(rk_head->u[2], reg2, w1, w2);
        ARIA_DEC_DIFF_BYTE(rk_head->u[3], reg3, w1, w2);

        ARIA_DIFF_WORD(reg0, reg1, reg2, reg3);
        ARIA_DIFF_BYTE(reg0, reg1, reg2, reg3);
        ARIA_DIFF_WORD(reg0, reg1, reg2, reg3);

        s0 = reg0;
        s1 = reg1;
        s2 = reg2;
        s3 = reg3;

        ARIA_DEC_DIFF_BYTE(rk_tail->u[0], reg0, w1, w2);
        ARIA_DEC_DIFF_BYTE(rk_tail->u[1], reg1, w1, w2);
        ARIA_DEC_DIFF_BYTE(rk_tail->u[2], reg2, w1, w2);
        ARIA_DEC_DIFF_BYTE(rk_tail->u[3], reg3, w1, w2);

        ARIA_DIFF_WORD(reg0, reg1, reg2, reg3);
        ARIA_DIFF_BYTE(reg0, reg1, reg2, reg3);
        ARIA_DIFF_WORD(reg0, reg1, reg2, reg3);

        rk_head->u[0] = reg0;
        rk_head->u[1] = reg1;
        rk_head->u[2] = reg2;
        rk_head->u[3] = reg3;

        rk_tail->u[0] = s0;
        rk_tail->u[1] = s1;
        rk_tail->u[2] = s2;
        rk_tail->u[3] = s3;
    }
    ARIA_DEC_DIFF_BYTE(rk_head->u[0], reg0, w1, w2);
    ARIA_DEC_DIFF_BYTE(rk_head->u[1], reg1, w1, w2);
    ARIA_DEC_DIFF_BYTE(rk_head->u[2], reg2, w1, w2);
    ARIA_DEC_DIFF_BYTE(rk_head->u[3], reg3, w1, w2);

    ARIA_DIFF_WORD(reg0, reg1, reg2, reg3);
    ARIA_DIFF_BYTE(reg0, reg1, reg2, reg3);
    ARIA_DIFF_WORD(reg0, reg1, reg2, reg3);

    rk_tail->u[0] = reg0;
    rk_tail->u[1] = reg1;
    rk_tail->u[2] = reg2;
    rk_tail->u[3] = reg3;

    return 0;
}