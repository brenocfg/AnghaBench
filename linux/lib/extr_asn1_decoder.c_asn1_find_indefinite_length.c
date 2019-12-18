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
typedef  int /*<<< orphan*/  len ;

/* Variables and functions */
 unsigned char ASN1_CONS_BIT ; 
 unsigned char ASN1_EOC ; 
 size_t ASN1_INDEFINITE_LENGTH ; 
 unsigned char ASN1_LONG_TAG ; 
 unsigned char ASN1_PRIM ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int asn1_find_indefinite_length(const unsigned char *data, size_t datalen,
				       size_t *_dp, size_t *_len,
				       const char **_errmsg)
{
	unsigned char tag, tmp;
	size_t dp = *_dp, len, n;
	int indef_level = 1;

next_tag:
	if (unlikely(datalen - dp < 2)) {
		if (datalen == dp)
			goto missing_eoc;
		goto data_overrun_error;
	}

	/* Extract a tag from the data */
	tag = data[dp++];
	if (tag == ASN1_EOC) {
		/* It appears to be an EOC. */
		if (data[dp++] != 0)
			goto invalid_eoc;
		if (--indef_level <= 0) {
			*_len = dp - *_dp;
			*_dp = dp;
			return 0;
		}
		goto next_tag;
	}

	if (unlikely((tag & 0x1f) == ASN1_LONG_TAG)) {
		do {
			if (unlikely(datalen - dp < 2))
				goto data_overrun_error;
			tmp = data[dp++];
		} while (tmp & 0x80);
	}

	/* Extract the length */
	len = data[dp++];
	if (len <= 0x7f)
		goto check_length;

	if (unlikely(len == ASN1_INDEFINITE_LENGTH)) {
		/* Indefinite length */
		if (unlikely((tag & ASN1_CONS_BIT) == ASN1_PRIM << 5))
			goto indefinite_len_primitive;
		indef_level++;
		goto next_tag;
	}

	n = len - 0x80;
	if (unlikely(n > sizeof(len) - 1))
		goto length_too_long;
	if (unlikely(n > datalen - dp))
		goto data_overrun_error;
	len = 0;
	for (; n > 0; n--) {
		len <<= 8;
		len |= data[dp++];
	}
check_length:
	if (len > datalen - dp)
		goto data_overrun_error;
	dp += len;
	goto next_tag;

length_too_long:
	*_errmsg = "Unsupported length";
	goto error;
indefinite_len_primitive:
	*_errmsg = "Indefinite len primitive not permitted";
	goto error;
invalid_eoc:
	*_errmsg = "Invalid length EOC";
	goto error;
data_overrun_error:
	*_errmsg = "Data overrun error";
	goto error;
missing_eoc:
	*_errmsg = "Missing EOC in indefinite len cons";
error:
	*_dp = dp;
	return -1;
}