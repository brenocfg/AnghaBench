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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
#define  FILE_FMT_DOUBLE 132 
#define  FILE_FMT_FLOAT 131 
#define  FILE_FMT_NUM 130 
#define  FILE_FMT_QUAD 129 
#define  FILE_FMT_STR 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  isdigit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_format_type(const char *ptr, int type) {
	int quad = 0;
	if (*ptr == '\0') {
		/* Missing format string; bad */
		return -1;
	}

	switch (type) {
	case FILE_FMT_QUAD:
		quad = 1;
		/*FALLTHROUGH*/
	case FILE_FMT_NUM:
		if (*ptr == '-') {
			ptr++;
		}
		if (*ptr == '.') {
			ptr++;
		}
		while (isdigit ((ut8)*ptr)) {
			ptr++;
		}
		if (*ptr == '.') {
			ptr++;
		}
		while (isdigit ((ut8)*ptr)) {
			ptr++;
		}
		if (quad) {
			if (*ptr++ != 'l') {
				return -1;
			}
			if (*ptr++ != 'l') {
				return -1;
			}
		}
		switch (*ptr++) {
		case 'l':
			switch (*ptr++) {
			case 'i':
			case 'd':
			case 'u':
			case 'x':
			case 'X':
				return 0;
			default:
				return -1;
			}
		case 'h':
			switch (*ptr++) {
			case 'h':
				switch (*ptr++) {
				case 'i':
				case 'd':
				case 'u':
				case 'x':
				case 'X':
					return 0;
				default:
					return -1;
				}
			case 'd':
				return 0;
			default:
				return -1;
			}
		case 'i':
		case 'c':
		case 'd':
		case 'u':
		case 'x':
		case 'X':
			return 0;
		default:
			return -1;
		}
	case FILE_FMT_FLOAT:
	case FILE_FMT_DOUBLE:
		if (*ptr == '-') {
			ptr++;
		}
		if (*ptr == '.') {
			ptr++;
		}
		while (isdigit ((ut8)*ptr)) {
			ptr++;
		}
		if (*ptr == '.') {
			ptr++;
		}
		while (isdigit ((ut8)*ptr)) {
			ptr++;
		}

		switch (*ptr++) {
		case 'e':
		case 'E':
		case 'f':
		case 'F':
		case 'g':
		case 'G':
			return 0;

		default:
			return -1;
		}
	case FILE_FMT_STR:
		if (*ptr == '-') {
			ptr++;
		}
		while (isdigit ((ut8)*ptr)) {
			ptr++;
		}
		if (*ptr == '.') {
			ptr++;
			while (isdigit ((ut8)*ptr)) {
				ptr++;
			}
		}

		if (*ptr++ == 's') {
			return 0;
		}
		return -1;
	default:
		/* internal error */
		abort ();
	}
	/*NOTREACHED*/
	return -1;
}