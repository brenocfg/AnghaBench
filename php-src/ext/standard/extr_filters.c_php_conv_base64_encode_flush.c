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
typedef  int /*<<< orphan*/  volatile php_conv_err_t ;
struct TYPE_3__ {unsigned int line_ccnt; int erem_len; size_t lbchars_len; unsigned int line_len; int* erem; int /*<<< orphan*/ * lbchars; } ;
typedef  TYPE_1__ php_conv_base64_encode ;

/* Variables and functions */
 int /*<<< orphan*/  volatile PHP_CONV_ERR_SUCCESS ; 
 int /*<<< orphan*/  volatile PHP_CONV_ERR_TOO_BIG ; 
 int /*<<< orphan*/  volatile PHP_CONV_ERR_UNKNOWN ; 
 void** b64_tbl_enc ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static php_conv_err_t php_conv_base64_encode_flush(php_conv_base64_encode *inst, const char **in_pp, size_t *in_left_p, char **out_pp, size_t *out_left_p)
{
	volatile php_conv_err_t err = PHP_CONV_ERR_SUCCESS;
	register unsigned char *pd;
	register size_t ocnt;
	unsigned int line_ccnt;

	pd = (unsigned char *)(*out_pp);
	ocnt = *out_left_p;
	line_ccnt = inst->line_ccnt;

	switch (inst->erem_len) {
		case 0:
			/* do nothing */
			break;

		case 1:
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
			*(pd++) = b64_tbl_enc[(unsigned char)(inst->erem[0] << 4)];
			*(pd++) = '=';
			*(pd++) = '=';
			inst->erem_len = 0;
			ocnt -= 4;
			line_ccnt -= 4;
			break;

		case 2:
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
			*(pd++) = b64_tbl_enc[(unsigned char)(inst->erem[0] << 4) | (inst->erem[1] >> 4)];
			*(pd++) = b64_tbl_enc[(unsigned char)(inst->erem[1] << 2)];
			*(pd++) = '=';
			inst->erem_len = 0;
			ocnt -=4;
			line_ccnt -= 4;
			break;

		default:
			/* should not happen... */
			err = PHP_CONV_ERR_UNKNOWN;
			break;
	}
out:
	*out_pp = (char *)pd;
	*out_left_p = ocnt;
	inst->line_ccnt = line_ccnt;
	return err;
}