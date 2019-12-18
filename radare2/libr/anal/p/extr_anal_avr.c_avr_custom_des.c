#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
typedef  int ut32 ;
struct TYPE_10__ {int round; int /*<<< orphan*/ * round_key_hi; int /*<<< orphan*/ * round_key_lo; } ;
struct TYPE_9__ {TYPE_1__* anal; } ;
struct TYPE_8__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ RAnalEsil ;

/* Variables and functions */
 int UT32_MAX ; 
 int /*<<< orphan*/  __esil_pop_argument (TYPE_2__*,int*) ; 
 TYPE_5__ desctx ; 
 int /*<<< orphan*/  r_anal_esil_reg_read (TYPE_2__*,char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_anal_esil_reg_write (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  r_des_permute_block0 (int*,int*) ; 
 int /*<<< orphan*/  r_des_permute_block1 (int*,int*) ; 
 int /*<<< orphan*/  r_des_permute_key (int*,int*) ; 
 int /*<<< orphan*/  r_des_round (int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_des_round_key (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static bool avr_custom_des (RAnalEsil *esil) {
	ut64 key, encrypt, text,des_round;
	ut32 key_lo, key_hi, buf_lo, buf_hi;
	if (!esil || !esil->anal || !esil->anal->reg) {
		return false;
	}
	if (!__esil_pop_argument (esil, &des_round)) {
		return false;
	}
	r_anal_esil_reg_read (esil, "hf", &encrypt, NULL);
	r_anal_esil_reg_read (esil, "deskey", &key, NULL);
	r_anal_esil_reg_read (esil, "text", &text, NULL);

	key_lo = key & UT32_MAX;
	key_hi = key >> 32;
	buf_lo = text & UT32_MAX;
	buf_hi = text >> 32;

	if (des_round != desctx.round) {
		desctx.round = des_round;
	}

	if (!desctx.round) {
		int i;
		//generating all round keys
		r_des_permute_key (&key_lo, &key_hi);
		for (i = 0; i < 16; i++) {
			r_des_round_key (i, &desctx.round_key_lo[i], &desctx.round_key_hi[i], &key_lo, &key_hi);
		}
		r_des_permute_block0 (&buf_lo, &buf_hi);
	}

	if (encrypt) {
		r_des_round (&buf_lo, &buf_hi, &desctx.round_key_lo[desctx.round], &desctx.round_key_hi[desctx.round]);
	} else {
		r_des_round (&buf_lo, &buf_hi, &desctx.round_key_lo[15 - desctx.round], &desctx.round_key_hi[15 - desctx.round]);
	}

	if (desctx.round == 15) {
		r_des_permute_block1 (&buf_hi, &buf_lo);
		desctx.round = 0;
	} else {
		desctx.round++;
	}

	r_anal_esil_reg_write (esil, "text", text);
	return true;
}