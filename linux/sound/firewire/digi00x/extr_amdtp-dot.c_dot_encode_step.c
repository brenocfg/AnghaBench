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
typedef  int u8 ;
struct dot_state {int idx; int carry; scalar_t__ off; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 size_t MAGIC_DOT_BYTE ; 
 int dot_scrt (int,scalar_t__) ; 

__attribute__((used)) static void dot_encode_step(struct dot_state *state, __be32 *const buffer)
{
	u8 * const data = (u8 *) buffer;

	if (data[MAGIC_DOT_BYTE] != 0x00) {
		state->off = 0;
		state->idx = data[MAGIC_DOT_BYTE] ^ state->carry;
	}
	data[MAGIC_DOT_BYTE] ^= state->carry;
	state->carry = dot_scrt(state->idx, ++(state->off));
}