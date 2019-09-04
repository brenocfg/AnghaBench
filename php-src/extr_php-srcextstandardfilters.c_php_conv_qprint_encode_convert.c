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
struct TYPE_3__ {unsigned int line_ccnt; int opts; unsigned int lb_ptr; unsigned int lb_cnt; unsigned char* lbchars; unsigned int lbchars_len; unsigned int line_len; } ;
typedef  TYPE_1__ php_conv_qprint_encode ;
typedef  int /*<<< orphan*/  php_conv_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONSUME_CHAR (unsigned char*,size_t,unsigned int,unsigned int) ; 
 unsigned int NEXT_CHAR (unsigned char*,size_t,unsigned int,unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  PHP_CONV_ERR_SUCCESS ; 
 int /*<<< orphan*/  PHP_CONV_ERR_TOO_BIG ; 
 int PHP_CONV_QPRINT_OPT_BINARY ; 
 int PHP_CONV_QPRINT_OPT_FORCE_ENCODE_FIRST ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static php_conv_err_t php_conv_qprint_encode_convert(php_conv_qprint_encode *inst, const char **in_pp, size_t *in_left_p, char **out_pp, size_t *out_left_p)
{
	php_conv_err_t err = PHP_CONV_ERR_SUCCESS;
	unsigned char *ps, *pd;
	size_t icnt, ocnt;
	unsigned int c;
	unsigned int line_ccnt;
	unsigned int lb_ptr;
	unsigned int lb_cnt;
	unsigned int trail_ws;
	int opts;
	static char qp_digits[] = "0123456789ABCDEF";

	line_ccnt = inst->line_ccnt;
	opts = inst->opts;
	lb_ptr = inst->lb_ptr;
	lb_cnt = inst->lb_cnt;

	if ((in_pp == NULL || in_left_p == NULL) && (lb_ptr >=lb_cnt)) {
		return PHP_CONV_ERR_SUCCESS;
	}

	ps = (unsigned char *)(*in_pp);
	icnt = *in_left_p;
	pd = (unsigned char *)(*out_pp);
	ocnt = *out_left_p;
	trail_ws = 0;

	for (;;) {
		if (!(opts & PHP_CONV_QPRINT_OPT_BINARY) && inst->lbchars != NULL && inst->lbchars_len > 0) {
			/* look ahead for the line break chars to make a right decision
			 * how to consume incoming characters */

			if (icnt > 0 && *ps == inst->lbchars[lb_cnt]) {
				lb_cnt++;

				if (lb_cnt >= inst->lbchars_len) {
					unsigned int i;

					if (ocnt < lb_cnt) {
						lb_cnt--;
						err = PHP_CONV_ERR_TOO_BIG;
						break;
					}

					for (i = 0; i < lb_cnt; i++) {
						*(pd++) = inst->lbchars[i];
						ocnt--;
					}
					line_ccnt = inst->line_len;
					lb_ptr = lb_cnt = 0;
				}
				ps++, icnt--;
				continue;
			}
		}

		if (lb_ptr >= lb_cnt && icnt == 0) {
			break;
		}

		c = NEXT_CHAR(ps, icnt, lb_ptr, lb_cnt, inst->lbchars);

		if (!(opts & PHP_CONV_QPRINT_OPT_BINARY) &&
			(trail_ws == 0) &&
			(c == '\t' || c == ' ')) {
			if (line_ccnt < 2 && inst->lbchars != NULL) {
				if (ocnt < inst->lbchars_len + 1) {
					err = PHP_CONV_ERR_TOO_BIG;
					break;
				}

				*(pd++) = '=';
				ocnt--;
				line_ccnt--;

				memcpy(pd, inst->lbchars, inst->lbchars_len);
				pd += inst->lbchars_len;
				ocnt -= inst->lbchars_len;
				line_ccnt = inst->line_len;
			} else {
				if (ocnt < 1) {
					err = PHP_CONV_ERR_TOO_BIG;
					break;
				}

				/* Check to see if this is EOL whitespace. */
				if (inst->lbchars != NULL) {
					unsigned char *ps2;
					unsigned int lb_cnt2;
					size_t j;

					lb_cnt2 = 0;
					ps2 = ps;
					trail_ws = 1;

					for (j = icnt - 1; j > 0; j--, ps2++) {
						if (*ps2 == inst->lbchars[lb_cnt2]) {
							lb_cnt2++;
							if (lb_cnt2 >= inst->lbchars_len) {
								/* Found trailing ws. Reset to top of main
								 * for loop to allow for code to do necessary
								 * wrapping/encoding. */
								break;
							}
						} else if (lb_cnt2 != 0 || (*ps2 != '\t' && *ps2 != ' ')) {
							/* At least one non-EOL character following, so
							 * don't need to encode ws. */
							trail_ws = 0;
							break;
						} else {
							trail_ws++;
						}
					}
				}

				if (trail_ws == 0) {
					*(pd++) = c;
					ocnt--;
					line_ccnt--;
					CONSUME_CHAR(ps, icnt, lb_ptr, lb_cnt);
				}
			}
		} else if ((!(opts & PHP_CONV_QPRINT_OPT_FORCE_ENCODE_FIRST) || line_ccnt < inst->line_len) && ((c >= 33 && c <= 60) || (c >= 62 && c <= 126))) {
			if (line_ccnt < 2 && inst->lbchars != NULL) {
				if (ocnt < inst->lbchars_len + 1) {
					err = PHP_CONV_ERR_TOO_BIG;
					break;
				}
				*(pd++) = '=';
				ocnt--;
				line_ccnt--;

				memcpy(pd, inst->lbchars, inst->lbchars_len);
				pd += inst->lbchars_len;
				ocnt -= inst->lbchars_len;
				line_ccnt = inst->line_len;
			}
			if (ocnt < 1) {
				err = PHP_CONV_ERR_TOO_BIG;
				break;
			}
			*(pd++) = c;
			ocnt--;
			line_ccnt--;
			CONSUME_CHAR(ps, icnt, lb_ptr, lb_cnt);
		} else {
			if (line_ccnt < 4 && inst->lbchars != NULL) {
				if (ocnt < inst->lbchars_len + 1) {
					err = PHP_CONV_ERR_TOO_BIG;
					break;
				}
				*(pd++) = '=';
				ocnt--;
				line_ccnt--;

				memcpy(pd, inst->lbchars, inst->lbchars_len);
				pd += inst->lbchars_len;
				ocnt -= inst->lbchars_len;
				line_ccnt = inst->line_len;
			}
			if (ocnt < 3) {
				err = PHP_CONV_ERR_TOO_BIG;
				break;
			}
			*(pd++) = '=';
			*(pd++) = qp_digits[(c >> 4)];
			*(pd++) = qp_digits[(c & 0x0f)];
			ocnt -= 3;
			line_ccnt -= 3;
			if (trail_ws > 0) {
				trail_ws--;
			}
			CONSUME_CHAR(ps, icnt, lb_ptr, lb_cnt);
		}
	}

	*in_pp = (const char *)ps;
	*in_left_p = icnt;
	*out_pp = (char *)pd;
	*out_left_p = ocnt;
	inst->line_ccnt = line_ccnt;
	inst->lb_ptr = lb_ptr;
	inst->lb_cnt = lb_cnt;
	return err;
}