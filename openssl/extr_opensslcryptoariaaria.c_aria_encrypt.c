#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int rounds; TYPE_1__* rd_key; } ;
struct TYPE_5__ {int* u; } ;
typedef  TYPE_1__ ARIA_u128 ;
typedef  TYPE_2__ ARIA_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  ARIA_ADD_ROUND_KEY (TYPE_1__ const*,int,int,int,int) ; 
 int /*<<< orphan*/  ARIA_SUBST_DIFF_EVEN (int,int,int,int) ; 
 int /*<<< orphan*/  ARIA_SUBST_DIFF_ODD (int,int,int,int) ; 
 int GET_U32_BE (unsigned char const*,int) ; 
 size_t GET_U8_BE (int,int) ; 
 int MAKE_U32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_U32_BE (unsigned char*,int,int) ; 
 scalar_t__* S1 ; 
 scalar_t__* S2 ; 
 scalar_t__* X1 ; 
 int* X2 ; 

void aria_encrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key)
{
    register uint32_t reg0, reg1, reg2, reg3;
    int Nr;
    const ARIA_u128 *rk;

    if (in == NULL || out == NULL || key == NULL) {
        return;
    }

    rk = key->rd_key;
    Nr = key->rounds;

    if (Nr != 12 && Nr != 14 && Nr != 16) {
        return;
    }

    reg0 = GET_U32_BE(in, 0);
    reg1 = GET_U32_BE(in, 1);
    reg2 = GET_U32_BE(in, 2);
    reg3 = GET_U32_BE(in, 3);

    ARIA_ADD_ROUND_KEY(rk, reg0, reg1, reg2, reg3);
    rk++;

    ARIA_SUBST_DIFF_ODD(reg0, reg1, reg2, reg3);
    ARIA_ADD_ROUND_KEY(rk, reg0, reg1, reg2, reg3);
    rk++;

    while(Nr -= 2){
        ARIA_SUBST_DIFF_EVEN(reg0, reg1, reg2, reg3);
        ARIA_ADD_ROUND_KEY(rk, reg0, reg1, reg2, reg3);
        rk++;

        ARIA_SUBST_DIFF_ODD(reg0, reg1, reg2, reg3);
        ARIA_ADD_ROUND_KEY(rk, reg0, reg1, reg2, reg3);
        rk++;
    }

    reg0 = rk->u[0] ^ MAKE_U32(
        (uint8_t)(X1[GET_U8_BE(reg0, 0)]     ),
        (uint8_t)(X2[GET_U8_BE(reg0, 1)] >> 8),
        (uint8_t)(S1[GET_U8_BE(reg0, 2)]     ),
        (uint8_t)(S2[GET_U8_BE(reg0, 3)]     ));
    reg1 = rk->u[1] ^ MAKE_U32(
        (uint8_t)(X1[GET_U8_BE(reg1, 0)]     ),
        (uint8_t)(X2[GET_U8_BE(reg1, 1)] >> 8),
        (uint8_t)(S1[GET_U8_BE(reg1, 2)]     ),
        (uint8_t)(S2[GET_U8_BE(reg1, 3)]     ));
    reg2 = rk->u[2] ^ MAKE_U32(
        (uint8_t)(X1[GET_U8_BE(reg2, 0)]     ),
        (uint8_t)(X2[GET_U8_BE(reg2, 1)] >> 8),
        (uint8_t)(S1[GET_U8_BE(reg2, 2)]     ),
        (uint8_t)(S2[GET_U8_BE(reg2, 3)]     ));
    reg3 = rk->u[3] ^ MAKE_U32(
        (uint8_t)(X1[GET_U8_BE(reg3, 0)]     ),
        (uint8_t)(X2[GET_U8_BE(reg3, 1)] >> 8),
        (uint8_t)(S1[GET_U8_BE(reg3, 2)]     ),
        (uint8_t)(S2[GET_U8_BE(reg3, 3)]     ));

    PUT_U32_BE(out, 0, reg0);
    PUT_U32_BE(out, 1, reg1);
    PUT_U32_BE(out, 2, reg2);
    PUT_U32_BE(out, 3, reg3);
}