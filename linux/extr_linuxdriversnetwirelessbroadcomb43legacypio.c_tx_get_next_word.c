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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 tx_get_next_word(const u8 *txhdr,
			    const u8 *packet,
			    size_t txhdr_size,
			    unsigned int *pos)
{
	const u8 *source;
	unsigned int i = *pos;
	u16 ret;

	if (i < txhdr_size)
		source = txhdr;
	else {
		source = packet;
		i -= txhdr_size;
	}
	ret = le16_to_cpu(*((__le16 *)(source + i)));
	*pos += 2;

	return ret;
}