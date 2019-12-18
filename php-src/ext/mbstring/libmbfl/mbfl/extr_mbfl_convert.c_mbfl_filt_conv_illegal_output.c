#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int illegal_mode; int illegal_substchar; int (* filter_function ) (int,TYPE_1__*) ;int /*<<< orphan*/  num_illegalchar; } ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
#define  MBFL_OUTPUTFILTER_ILLEGAL_MODE_CHAR 137 
#define  MBFL_OUTPUTFILTER_ILLEGAL_MODE_ENTITY 136 
#define  MBFL_OUTPUTFILTER_ILLEGAL_MODE_LONG 135 
#define  MBFL_OUTPUTFILTER_ILLEGAL_MODE_NONE 134 
 int MBFL_WCSGROUP_MASK ; 
 int MBFL_WCSGROUP_UCS4MAX ; 
 int MBFL_WCSGROUP_WCHARMAX ; 
#define  MBFL_WCSPLANE_8859_1 133 
#define  MBFL_WCSPLANE_GB18030 132 
#define  MBFL_WCSPLANE_JIS0208 131 
#define  MBFL_WCSPLANE_JIS0212 130 
#define  MBFL_WCSPLANE_JIS0213 129 
 int MBFL_WCSPLANE_MASK ; 
#define  MBFL_WCSPLANE_WINCP932 128 
 int mbfl_convert_filter_strcat (TYPE_1__*,unsigned char const*) ; 
 int* mbfl_hexchar_table ; 
 int stub1 (int,TYPE_1__*) ; 
 int stub2 (int,TYPE_1__*) ; 
 int stub3 (int,TYPE_1__*) ; 
 int stub4 (int,TYPE_1__*) ; 
 int stub5 (int,TYPE_1__*) ; 
 int stub6 (int,TYPE_1__*) ; 

int
mbfl_filt_conv_illegal_output(int c, mbfl_convert_filter *filter)
{
	int mode_backup, substchar_backup, ret, n, m, r;

	ret = 0;

	mode_backup = filter->illegal_mode;
	substchar_backup = filter->illegal_substchar;

	/* The used substitution character may not be supported by the target character encoding.
	 * If that happens, first try to use "?" instead and if that also fails, silently drop the
	 * character. */
	if (filter->illegal_mode == MBFL_OUTPUTFILTER_ILLEGAL_MODE_CHAR
			&& filter->illegal_substchar != 0x3f) {
		filter->illegal_substchar = 0x3f;
	} else {
		filter->illegal_mode = MBFL_OUTPUTFILTER_ILLEGAL_MODE_NONE;
	}

	switch (mode_backup) {
	case MBFL_OUTPUTFILTER_ILLEGAL_MODE_CHAR:
		ret = (*filter->filter_function)(substchar_backup, filter);
		break;
	case MBFL_OUTPUTFILTER_ILLEGAL_MODE_LONG:
		if (c >= 0) {
			if (c < MBFL_WCSGROUP_UCS4MAX) {	/* unicode */
				ret = mbfl_convert_filter_strcat(filter, (const unsigned char *)"U+");
			} else {
				if (c < MBFL_WCSGROUP_WCHARMAX) {
					m = c & ~MBFL_WCSPLANE_MASK;
					switch (m) {
					case MBFL_WCSPLANE_JIS0208:
						ret = mbfl_convert_filter_strcat(filter, (const unsigned char *)"JIS+");
						break;
					case MBFL_WCSPLANE_JIS0212:
						ret = mbfl_convert_filter_strcat(filter, (const unsigned char *)"JIS2+");
						break;
					case MBFL_WCSPLANE_JIS0213:
						ret = mbfl_convert_filter_strcat(filter, (const unsigned char *)"JIS3+");
						break;
					case MBFL_WCSPLANE_WINCP932:
						ret = mbfl_convert_filter_strcat(filter, (const unsigned char *)"W932+");
						break;
					case MBFL_WCSPLANE_GB18030:
						ret = mbfl_convert_filter_strcat(filter, (const unsigned char *)"GB+");
						break;
					case MBFL_WCSPLANE_8859_1:
						ret = mbfl_convert_filter_strcat(filter, (const unsigned char *)"I8859_1+");
						break;
					default:
						ret = mbfl_convert_filter_strcat(filter, (const unsigned char *)"?+");
						break;
					}
					c &= MBFL_WCSPLANE_MASK;
				} else {
					ret = mbfl_convert_filter_strcat(filter, (const unsigned char *)"BAD+");
					c &= MBFL_WCSGROUP_MASK;
				}
			}
			if (ret >= 0) {
				m = 0;
				r = 28;
				while (r >= 0) {
					n = (c >> r) & 0xf;
					if (n || m) {
						m = 1;
						ret = (*filter->filter_function)(mbfl_hexchar_table[n], filter);
						if (ret < 0) {
							break;
						}
					}
					r -= 4;
				}
				if (m == 0 && ret >= 0) {
					ret = (*filter->filter_function)(mbfl_hexchar_table[0], filter);
				}
			}
		}
		break;
	case MBFL_OUTPUTFILTER_ILLEGAL_MODE_ENTITY:
		if (c >= 0) {
			if (c < MBFL_WCSGROUP_UCS4MAX) {	/* unicode */
				ret = mbfl_convert_filter_strcat(filter, (const unsigned char *)"&#x");
				if (ret < 0)
					break;

				m = 0;
				r = 28;
				while (r >= 0) {
					n = (c >> r) & 0xf;
					if (n || m) {
						m = 1;
						ret = (*filter->filter_function)(mbfl_hexchar_table[n], filter);
						if (ret < 0) {
							break;
						}
					}
					r -= 4;
				}
				if (ret < 0) {
					break;
				}
				if (m == 0) {
					ret = (*filter->filter_function)(mbfl_hexchar_table[0], filter);
				}
				ret = mbfl_convert_filter_strcat(filter, (const unsigned char *)";");
			} else {
				ret = (*filter->filter_function)(substchar_backup, filter);
			}
		}
		break;
	case MBFL_OUTPUTFILTER_ILLEGAL_MODE_NONE:
	default:
		break;
	}

	filter->illegal_mode = mode_backup;
	filter->illegal_substchar = substchar_backup;
	filter->num_illegalchar++;

	return ret;
}