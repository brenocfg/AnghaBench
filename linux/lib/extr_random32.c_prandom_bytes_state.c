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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rnd_state {int dummy; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int prandom_u32_state (struct rnd_state*) ; 
 int /*<<< orphan*/  put_unaligned (int,int*) ; 

void prandom_bytes_state(struct rnd_state *state, void *buf, size_t bytes)
{
	u8 *ptr = buf;

	while (bytes >= sizeof(u32)) {
		put_unaligned(prandom_u32_state(state), (u32 *) ptr);
		ptr += sizeof(u32);
		bytes -= sizeof(u32);
	}

	if (bytes > 0) {
		u32 rem = prandom_u32_state(state);
		do {
			*ptr++ = (u8) rem;
			bytes--;
			rem >>= BITS_PER_BYTE;
		} while (bytes > 0);
	}
}