#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  volatile php_conv_err_t ;
struct TYPE_4__ {unsigned int line_ccnt; size_t lbchars_len; unsigned int line_len; int* erem; scalar_t__ erem_len; int /*<<< orphan*/ * lbchars; } ;
typedef  TYPE_1__ php_conv_base64_encode ;

/* Variables and functions */
 int /*<<< orphan*/  volatile PHP_CONV_ERR_SUCCESS ; 
 int /*<<< orphan*/  volatile PHP_CONV_ERR_TOO_BIG ; 
 void** b64_tbl_enc ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  volatile php_conv_base64_encode_flush (TYPE_1__*,char const**,size_t*,char**,size_t*) ; 

__attribute__((used)) static php_conv_err_t php_conv_base64_encode_convert(php_conv_base64_encode *inst, const char **in_pp, size_t *in_left_p, char **out_pp, size_t *out_left_p)
{
	volatile php_conv_err_t err = PHP_CONV_ERR_SUCCESS;
	register size_t ocnt, icnt;
	register unsigned char *ps, *pd;
	register unsigned int line_ccnt;

	if (in_pp == NULL || in_left_p == NULL) {
		return php_conv_base64_encode_flush(inst, in_pp, in_left_p, out_pp, out_left_p);
	}

	pd = (unsigned char *)(*out_pp);
	ocnt = *out_left_p;
	ps = (unsigned char *)(*in_pp);
	icnt = *in_left_p;
	line_ccnt = inst->line_ccnt;

	/* consume the remainder first */
	switch (inst->erem_len) {
		case 1:
			if (icnt >= 2) {
				if (line_ccnt < 4 && inst->lbchars != NULL) {
					if (ocnt < inst->lbchars_len) {
						return PHP_CONV_ERR_TOO_BIG;
					}
					memcpy(pd, inst->lbchars, inst->lbchars_len);
					pd += inst->lbchars_len;
					ocnt -= inst->lbchars_len;
					line_ccnt = inst->line_len;
				}
				if (ocnt < 4) {
					err = PHP_CONV_ERR_TOO_BIG;
					goto out;
				}
				*(pd++) = b64_tbl_enc[(inst->erem[0] >> 2)];
				*(pd++) = b64_tbl_enc[(unsigned char)(inst->erem[0] << 4) | (ps[0] >> 4)];
				*(pd++) = b64_tbl_enc[(unsigned char)(ps[0] << 2) | (ps[1] >> 6)];
				*(pd++) = b64_tbl_enc[ps[1]];
				ocnt -= 4;
				ps += 2;
				icnt -= 2;
				inst->erem_len = 0;
				line_ccnt -= 4;
			}
			break;

		case 2:
			if (icnt >= 1) {
				if (inst->line_ccnt < 4 && inst->lbchars != NULL) {
					if (ocnt < inst->lbchars_len) {
						return PHP_CONV_ERR_TOO_BIG;
					}
					memcpy(pd, inst->lbchars, inst->lbchars_len);
					pd += inst->lbchars_len;
					ocnt -= inst->lbchars_len;
					line_ccnt = inst->line_len;
				}
				if (ocnt < 4) {
					err = PHP_CONV_ERR_TOO_BIG;
					goto out;
				}
				*(pd++) = b64_tbl_enc[(inst->erem[0] >> 2)];
				*(pd++) = b64_tbl_enc[(unsigned char)(inst->erem[0] << 4) | (inst->erem[1] >> 4)];
				*(pd++) = b64_tbl_enc[(unsigned char)(inst->erem[1] << 2) | (ps[0] >> 6)];
				*(pd++) = b64_tbl_enc[ps[0]];
				ocnt -= 4;
				ps += 1;
				icnt -= 1;
				inst->erem_len = 0;
				line_ccnt -= 4;
			}
			break;
	}

	while (icnt >= 3) {
		if (line_ccnt < 4 && inst->lbchars != NULL) {
			if (ocnt < inst->lbchars_len) {
				err = PHP_CONV_ERR_TOO_BIG;
				goto out;
			}
			memcpy(pd, inst->lbchars, inst->lbchars_len);
			pd += inst->lbchars_len;
			ocnt -= inst->lbchars_len;
			line_ccnt = inst->line_len;
		}
		if (ocnt < 4) {
			err = PHP_CONV_ERR_TOO_BIG;
			goto out;
		}
		*(pd++) = b64_tbl_enc[ps[0] >> 2];
		*(pd++) = b64_tbl_enc[(unsigned char)(ps[0] << 4) | (ps[1] >> 4)];
		*(pd++) = b64_tbl_enc[(unsigned char)(ps[1] << 2) | (ps[2] >> 6)];
		*(pd++) = b64_tbl_enc[ps[2]];

		ps += 3;
		icnt -=3;
		ocnt -= 4;
		line_ccnt -= 4;
	}
	for (;icnt > 0; icnt--) {
		inst->erem[inst->erem_len++] = *(ps++);
	}

out:
	*in_pp = (const char *)ps;
	*in_left_p = icnt;
	*out_pp = (char *)pd;
	*out_left_p = ocnt;
	inst->line_ccnt = line_ccnt;

	return err;
}