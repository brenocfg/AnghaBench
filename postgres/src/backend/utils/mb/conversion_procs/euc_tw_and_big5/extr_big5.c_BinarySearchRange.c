#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned short code; int peer; } ;
typedef  TYPE_1__ codes_t ;

/* Variables and functions */

__attribute__((used)) static unsigned short BinarySearchRange
			(const codes_t *array, int high, unsigned short code)
{
	int			low,
				mid,
				distance,
				tmp;

	low = 0;
	mid = high >> 1;

	for (; low <= high; mid = (low + high) >> 1)
	{
		if ((array[mid].code <= code) && (array[mid + 1].code > code))
		{
			if (0 == array[mid].peer)
				return 0;
			if (code >= 0xa140U)
			{
				/* big5 to cns */
				tmp = ((code & 0xff00) - (array[mid].code & 0xff00)) >> 8;
				high = code & 0x00ff;
				low = array[mid].code & 0x00ff;

				/*
				 * NOTE: big5 high_byte: 0xa1-0xfe, low_byte: 0x40-0x7e,
				 * 0xa1-0xfe (radicals: 0x00-0x3e, 0x3f-0x9c) big5 radix is
				 * 0x9d.                     [region_low, region_high] We
				 * should remember big5 has two different regions (above).
				 * There is a bias for the distance between these regions.
				 * 0xa1 - 0x7e + bias = 1 (Distance between 0xa1 and 0x7e is
				 * 1.) bias = - 0x22.
				 */
				distance = tmp * 0x9d + high - low +
					(high >= 0xa1 ? (low >= 0xa1 ? 0 : -0x22)
					 : (low >= 0xa1 ? +0x22 : 0));

				/*
				 * NOTE: we have to convert the distance into a code point.
				 * The code point's low_byte is 0x21 plus mod_0x5e. In the
				 * first, we extract the mod_0x5e of the starting code point,
				 * subtracting 0x21, and add distance to it. Then we calculate
				 * again mod_0x5e of them, and restore the final codepoint,
				 * adding 0x21.
				 */
				tmp = (array[mid].peer & 0x00ff) + distance - 0x21;
				tmp = (array[mid].peer & 0xff00) + ((tmp / 0x5e) << 8)
					+ 0x21 + tmp % 0x5e;
				return tmp;
			}
			else
			{
				/* cns to big5 */
				tmp = ((code & 0xff00) - (array[mid].code & 0xff00)) >> 8;

				/*
				 * NOTE: ISO charsets ranges between 0x21-0xfe (94charset).
				 * Its radix is 0x5e. But there is no distance bias like big5.
				 */
				distance = tmp * 0x5e
					+ ((int) (code & 0x00ff) - (int) (array[mid].code & 0x00ff));

				/*
				 * NOTE: Similar to big5 to cns conversion, we extract
				 * mod_0x9d and restore mod_0x9d into a code point.
				 */
				low = array[mid].peer & 0x00ff;
				tmp = low + distance - (low >= 0xa1 ? 0x62 : 0x40);
				low = tmp % 0x9d;
				tmp = (array[mid].peer & 0xff00) + ((tmp / 0x9d) << 8)
					+ (low > 0x3e ? 0x62 : 0x40) + low;
				return tmp;
			}
		}
		else if (array[mid].code > code)
			high = mid - 1;
		else
			low = mid + 1;
	}

	return 0;
}