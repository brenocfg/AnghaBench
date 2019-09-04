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
struct michael_mic {int* m; int m_bytes; int l; int r; } ;

/* Variables and functions */
 int /*<<< orphan*/  michael_block (struct michael_mic*) ; 
 int /*<<< orphan*/  michael_clear (struct michael_mic*) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int*) ; 

__attribute__((used)) static void michael_get_mic(struct michael_mic *mic, u8 *dst)
{
	u8 *data = mic->m;

	switch (mic->m_bytes) {
	case 0:
		mic->l ^= 0x5a;
		break;
	case 1:
		mic->l ^= data[0] | 0x5a00;
		break;
	case 2:
		mic->l ^= data[0] | (data[1] << 8) | 0x5a0000;
		break;
	case 3:
		mic->l ^= data[0] | (data[1] << 8) | (data[2] << 16) |
		    0x5a000000;
		break;
	}
	michael_block(mic);
	michael_block(mic);
	// The appendByte function has already computed the result.
	put_unaligned_le32(mic->l, dst);
	put_unaligned_le32(mic->r, dst + 4);

	// Reset to the empty message.
	michael_clear(mic);
}