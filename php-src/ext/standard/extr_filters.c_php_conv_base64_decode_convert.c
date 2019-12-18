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
typedef  int /*<<< orphan*/  php_conv_err_t ;
struct TYPE_3__ {int eos; unsigned int urem_nbits; unsigned int urem; unsigned int ustat; } ;
typedef  TYPE_1__ php_conv_base64_decode ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_CONV_ERR_INVALID_SEQ ; 
 int /*<<< orphan*/  PHP_CONV_ERR_SUCCESS ; 
 int /*<<< orphan*/  PHP_CONV_ERR_TOO_BIG ; 
 int /*<<< orphan*/  PHP_CONV_ERR_UNEXPECTED_EOS ; 
 unsigned int* b64_tbl_dec ; 
 unsigned int bmask (unsigned int) ; 

__attribute__((used)) static php_conv_err_t php_conv_base64_decode_convert(php_conv_base64_decode *inst, const char **in_pp, size_t *in_left_p, char **out_pp, size_t *out_left_p)
{
	php_conv_err_t err;

	unsigned int urem, urem_nbits;
	unsigned int pack, pack_bcnt;
	unsigned char *ps, *pd;
	size_t icnt, ocnt;
	unsigned int ustat;

	static const unsigned int nbitsof_pack = 8;

	if (in_pp == NULL || in_left_p == NULL) {
		if (inst->eos || inst->urem_nbits == 0) {
			return PHP_CONV_ERR_SUCCESS;
		}
		return PHP_CONV_ERR_UNEXPECTED_EOS;
	}

	err = PHP_CONV_ERR_SUCCESS;

	ps = (unsigned char *)*in_pp;
	pd = (unsigned char *)*out_pp;
	icnt = *in_left_p;
	ocnt = *out_left_p;

	urem = inst->urem;
	urem_nbits = inst->urem_nbits;
	ustat = inst->ustat;

	pack = 0;
	pack_bcnt = nbitsof_pack;

	for (;;) {
		if (pack_bcnt >= urem_nbits) {
			pack_bcnt -= urem_nbits;
			pack |= (urem << pack_bcnt);
			urem_nbits = 0;
		} else {
			urem_nbits -= pack_bcnt;
			pack |= (urem >> urem_nbits);
			urem &= bmask(urem_nbits);
			pack_bcnt = 0;
		}
		if (pack_bcnt > 0) {
			unsigned int i;

			if (icnt < 1) {
				break;
			}

			i = b64_tbl_dec[(unsigned int)*(ps++)];
			icnt--;
			ustat |= i & 0x80;

			if (!(i & 0xc0)) {
				if (ustat) {
					err = PHP_CONV_ERR_INVALID_SEQ;
					break;
				}
				if (6 <= pack_bcnt) {
					pack_bcnt -= 6;
					pack |= (i << pack_bcnt);
					urem = 0;
				} else {
					urem_nbits = 6 - pack_bcnt;
					pack |= (i >> urem_nbits);
					urem = i & bmask(urem_nbits);
					pack_bcnt = 0;
				}
			} else if (ustat) {
				if (pack_bcnt == 8 || pack_bcnt == 2) {
					err = PHP_CONV_ERR_INVALID_SEQ;
					break;
				}
				inst->eos = 1;
			}
		}
		if ((pack_bcnt | ustat) == 0) {
			if (ocnt < 1) {
				err = PHP_CONV_ERR_TOO_BIG;
				break;
			}
			*(pd++) = pack;
			ocnt--;
			pack = 0;
			pack_bcnt = nbitsof_pack;
		}
	}

	if (urem_nbits >= pack_bcnt) {
		urem |= (pack << (urem_nbits - pack_bcnt));
		urem_nbits += (nbitsof_pack - pack_bcnt);
	} else {
		urem |= (pack >> (pack_bcnt - urem_nbits));
		urem_nbits += (nbitsof_pack - pack_bcnt);
	}

	inst->urem = urem;
	inst->urem_nbits = urem_nbits;
	inst->ustat = ustat;

	*in_pp = (const char *)ps;
	*in_left_p = icnt;
	*out_pp = (char *)pd;
	*out_left_p = ocnt;

	return err;
}