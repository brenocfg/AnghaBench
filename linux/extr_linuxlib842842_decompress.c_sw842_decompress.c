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
typedef  int u64 ;
struct sw842_param {unsigned int ilen; unsigned int olen; int /*<<< orphan*/ * out; int /*<<< orphan*/ * ostart; scalar_t__ bit; int /*<<< orphan*/ * in; } ;

/* Variables and functions */
 int CRC_BITS ; 
 int EINVAL ; 
 int ENOSPC ; 
 int OP_BITS ; 
#define  OP_END 131 
#define  OP_REPEAT 130 
#define  OP_SHORT_DATA 129 
#define  OP_ZEROS 128 
 int REPEAT_BITS ; 
 int SHORT_DATA_BITS ; 
 int SHORT_DATA_BITS_MAX ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ crc32_be (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int do_op (struct sw842_param*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int next_bits (struct sw842_param*,int*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  sw842_template_counts ; 
 int /*<<< orphan*/  template_end_count ; 
 int /*<<< orphan*/  template_repeat_count ; 
 int /*<<< orphan*/  template_short_data_count ; 
 int /*<<< orphan*/  template_zeros_count ; 
 scalar_t__ unlikely (int) ; 

int sw842_decompress(const u8 *in, unsigned int ilen,
		     u8 *out, unsigned int *olen)
{
	struct sw842_param p;
	int ret;
	u64 op, rep, tmp, bytes, total;
	u64 crc;

	p.in = (u8 *)in;
	p.bit = 0;
	p.ilen = ilen;
	p.out = out;
	p.ostart = out;
	p.olen = *olen;

	total = p.olen;

	*olen = 0;

	do {
		ret = next_bits(&p, &op, OP_BITS);
		if (ret)
			return ret;

		pr_debug("template is %lx\n", (unsigned long)op);

		switch (op) {
		case OP_REPEAT:
			ret = next_bits(&p, &rep, REPEAT_BITS);
			if (ret)
				return ret;

			if (p.out == out) /* no previous bytes */
				return -EINVAL;

			/* copy rep + 1 */
			rep++;

			if (rep * 8 > p.olen)
				return -ENOSPC;

			while (rep-- > 0) {
				memcpy(p.out, p.out - 8, 8);
				p.out += 8;
				p.olen -= 8;
			}

			if (sw842_template_counts)
				atomic_inc(&template_repeat_count);

			break;
		case OP_ZEROS:
			if (8 > p.olen)
				return -ENOSPC;

			memset(p.out, 0, 8);
			p.out += 8;
			p.olen -= 8;

			if (sw842_template_counts)
				atomic_inc(&template_zeros_count);

			break;
		case OP_SHORT_DATA:
			ret = next_bits(&p, &bytes, SHORT_DATA_BITS);
			if (ret)
				return ret;

			if (!bytes || bytes > SHORT_DATA_BITS_MAX)
				return -EINVAL;

			while (bytes-- > 0) {
				ret = next_bits(&p, &tmp, 8);
				if (ret)
					return ret;
				*p.out = (u8)tmp;
				p.out++;
				p.olen--;
			}

			if (sw842_template_counts)
				atomic_inc(&template_short_data_count);

			break;
		case OP_END:
			if (sw842_template_counts)
				atomic_inc(&template_end_count);

			break;
		default: /* use template */
			ret = do_op(&p, op);
			if (ret)
				return ret;
			break;
		}
	} while (op != OP_END);

	/*
	 * crc(0:31) is saved in compressed data starting with the
	 * next bit after End of stream template.
	 */
	ret = next_bits(&p, &crc, CRC_BITS);
	if (ret)
		return ret;

	/*
	 * Validate CRC saved in compressed data.
	 */
	if (crc != (u64)crc32_be(0, out, total - p.olen)) {
		pr_debug("CRC mismatch for decompression\n");
		return -EINVAL;
	}

	if (unlikely((total - p.olen) > UINT_MAX))
		return -ENOSPC;

	*olen = total - p.olen;

	return 0;
}