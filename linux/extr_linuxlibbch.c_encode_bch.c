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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct bch_control {int* mod8_tab; int* ecc_buf; } ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int BCH_ECC_MAX_WORDS ; 
 int BCH_ECC_WORDS (struct bch_control*) ; 
 scalar_t__ WARN_ON (int) ; 
 int cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_bch_unaligned (struct bch_control*,int /*<<< orphan*/  const*,unsigned int,int*) ; 
 int /*<<< orphan*/  load_ecc8 (struct bch_control*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t const) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  store_ecc8 (struct bch_control*,int /*<<< orphan*/ *,int*) ; 

void encode_bch(struct bch_control *bch, const uint8_t *data,
		unsigned int len, uint8_t *ecc)
{
	const unsigned int l = BCH_ECC_WORDS(bch)-1;
	unsigned int i, mlen;
	unsigned long m;
	uint32_t w, r[BCH_ECC_MAX_WORDS];
	const size_t r_bytes = BCH_ECC_WORDS(bch) * sizeof(*r);
	const uint32_t * const tab0 = bch->mod8_tab;
	const uint32_t * const tab1 = tab0 + 256*(l+1);
	const uint32_t * const tab2 = tab1 + 256*(l+1);
	const uint32_t * const tab3 = tab2 + 256*(l+1);
	const uint32_t *pdata, *p0, *p1, *p2, *p3;

	if (WARN_ON(r_bytes > sizeof(r)))
		return;

	if (ecc) {
		/* load ecc parity bytes into internal 32-bit buffer */
		load_ecc8(bch, bch->ecc_buf, ecc);
	} else {
		memset(bch->ecc_buf, 0, r_bytes);
	}

	/* process first unaligned data bytes */
	m = ((unsigned long)data) & 3;
	if (m) {
		mlen = (len < (4-m)) ? len : 4-m;
		encode_bch_unaligned(bch, data, mlen, bch->ecc_buf);
		data += mlen;
		len  -= mlen;
	}

	/* process 32-bit aligned data words */
	pdata = (uint32_t *)data;
	mlen  = len/4;
	data += 4*mlen;
	len  -= 4*mlen;
	memcpy(r, bch->ecc_buf, r_bytes);

	/*
	 * split each 32-bit word into 4 polynomials of weight 8 as follows:
	 *
	 * 31 ...24  23 ...16  15 ... 8  7 ... 0
	 * xxxxxxxx  yyyyyyyy  zzzzzzzz  tttttttt
	 *                               tttttttt  mod g = r0 (precomputed)
	 *                     zzzzzzzz  00000000  mod g = r1 (precomputed)
	 *           yyyyyyyy  00000000  00000000  mod g = r2 (precomputed)
	 * xxxxxxxx  00000000  00000000  00000000  mod g = r3 (precomputed)
	 * xxxxxxxx  yyyyyyyy  zzzzzzzz  tttttttt  mod g = r0^r1^r2^r3
	 */
	while (mlen--) {
		/* input data is read in big-endian format */
		w = r[0]^cpu_to_be32(*pdata++);
		p0 = tab0 + (l+1)*((w >>  0) & 0xff);
		p1 = tab1 + (l+1)*((w >>  8) & 0xff);
		p2 = tab2 + (l+1)*((w >> 16) & 0xff);
		p3 = tab3 + (l+1)*((w >> 24) & 0xff);

		for (i = 0; i < l; i++)
			r[i] = r[i+1]^p0[i]^p1[i]^p2[i]^p3[i];

		r[l] = p0[l]^p1[l]^p2[l]^p3[l];
	}
	memcpy(bch->ecc_buf, r, r_bytes);

	/* process last unaligned bytes */
	if (len)
		encode_bch_unaligned(bch, data, len, bch->ecc_buf);

	/* store ecc parity bytes into original parity buffer */
	if (ecc)
		store_ecc8(bch, ecc, bch->ecc_buf);
}