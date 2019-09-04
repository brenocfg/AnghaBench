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
struct TYPE_3__ {int bits; int /*<<< orphan*/  sdb_types; int /*<<< orphan*/  formats; } ;
typedef  TYPE_1__ RPrint ;

/* Variables and functions */
 int R_PRINT_UNIONMODE ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int r_num_math (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ r_str_rchr (char*,int /*<<< orphan*/ *,char) ; 
 char* r_str_word_get0 (char*,int) ; 
 int r_str_word_set0_stack (char*) ; 
 char* r_type_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* sdb_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

int r_print_format_struct_size(const char *f, RPrint *p, int mode, int n) {
	char *end, *args, *fmt;
	int size = 0, tabsize = 0, i, idx = 0, biggest = 0, fmt_len = 0, times = 1;
	bool tabsize_set = false;
	if (!f) {
		return -1;
	}
	if (n >= 5) {  // This is the nesting level, is this not a bit arbitrary?!
		return 0;
	}
	char *o = strdup (f);
	if (!o) {
		return -1;
	}
	end = strchr (o, ' ');
	fmt = o;
	if (!end && !(end = strchr (o, '\0'))) {
		free (o);
		return -1;
	}
	if (*end) {
		*end = 0;
		args = strdup (end + 1);
	} else {
		args = strdup ("");
	}

	i = 0;
	if (fmt[i] == '{') {
		char *end = strchr (fmt + i + 1, '}');
		if (!end) {
			eprintf ("No end curly bracket.\n");
			free (o);
			free (args);
			return -1;
		}
		*end = '\0';
		times = r_num_math (NULL, fmt + i + 1);
		fmt = end + 1;
		i = 0;
	}
	if (fmt[0] == '0') {
		mode |= R_PRINT_UNIONMODE;
		fmt++;
	} else {
		mode &= ~R_PRINT_UNIONMODE;
	}

	int words = r_str_word_set0_stack (args);
	fmt_len = strlen (fmt);
	for (; i < fmt_len; i++) {
		if (fmt[i] == '[') {
			char *end = strchr (fmt + i,']');
			if (!end) {
				eprintf ("No end bracket.\n");
				continue;
			}
			*end = '\0';
			tabsize_set = true;
			tabsize = r_num_math (NULL, fmt + i + 1);
			*end = ']';
			while (fmt[i++] != ']') {
				;
			}
		} else {
			tabsize = 1;
		}

		switch (fmt[i]) {
		case '.':
			idx--;
		case 'c':
		case 'b':
		case 'X':
			size += tabsize * 1;
			break;
		case 'w':
			size += tabsize * 2;
			break;
		case ':':
			idx--;
		case 'd':
		case 'o':
		case 'i':
		case 'x':
		case 'f':
		case 's':
		case 't':
			size += tabsize * 4;
			break;
		case 'S':
		case 'q':
		case 'F':
			size += tabsize * 8;
			break;
		case 'z':
		case 'Z':
			size += tabsize;
			break;
		case '*':
			size += tabsize * (p->bits / 8);
			i++;
			idx--;	//no need to go ahead for args
			break;
		case 'B':
		case 'E':
			if (tabsize_set) {
				switch (tabsize) {
				case 1: size += 1; break;
				case 2: size += 2; break;
				case 4: size += 4; break;
				case 8: size += 8; break;
				default:
					eprintf ("Unknown enum format size: %d\n", tabsize);
					break;
				}
			} else {
				size += 4; // Assuming by default enum as int
			}
			break;
		case '?':
			{
			const char *wordAtIndex = NULL;
			const char *format = NULL;
			char *endname = NULL, *structname = NULL;
			char tmp = 0;
			if (words < idx) {
				eprintf ("Index out of bounds\n");
			} else {
				wordAtIndex = r_str_word_get0 (args, idx);
			}
			if (!wordAtIndex) {
				break;
			}
			structname = strdup (wordAtIndex);
			if (*structname == '(') {
				endname = (char*)r_str_rchr (structname, NULL, ')');
			} else {
				free (structname);
				break;
			}
			if (endname) {
				*endname = '\0';
			}
			format = strchr (structname, ' ');
			if (format) {
				tmp = *format;
				while (tmp == ' ') {
					format++;
					tmp = *format;
				}
			} else {
				format = sdb_get (p->formats, structname + 1, NULL);
				if (format && !strncmp (format, f, strlen (format) - 1)) { // Avoid recursion here
					free (o);
					free (structname);
					return -1;
				}
				if (!format) { // Fetch format from types db
					format = r_type_format (p->sdb_types, structname + 1);
				}
			}
			if (!format) {
				eprintf ("Cannot find format for struct `%s'\n", structname + 1);
				free (structname);
				free (o);
				return 0;
			}
			int newsize = r_print_format_struct_size (format, p, mode, n + 1);
			if (newsize < 1) {
				eprintf ("Cannot find size for `%s'\n", format);
				free (structname);
				free (o);
				return 0;
			}
			if (format && newsize > 0) {
				size += tabsize * newsize;
			}
			free (structname);
			}
			break;
		case '{':
			while (fmt[i] != '}') {
				if (!fmt[i]) {
					free (o);
					free (args);
					return -1;
				}
				i++;
			}
			i++;
			idx--;
			break;
		case '}':
			free (o);
			free (args);
			return -1;
		case '+':
		case 'e':
			idx--;
			break;
		case 'p':
			if (fmt[i+1] == '2') {
				size += tabsize * 2;
			} else if (fmt[i+1] == '4') {
				size += tabsize * 4;
			} else if (fmt[i+1] == '8') {
				size += tabsize * 8;
			} else {
				size += tabsize * (p->bits / 8);
				break;
			}
			i++;
			break;
		case 'r':
			break;
		case 'n':
		case 'N':
			if (fmt[i+1] == '1') {
				size += tabsize * 1;
			} else if (fmt[i+1] == '2') {
				size += tabsize * 2;
			} else if (fmt[i+1] == '4') {
				size += tabsize * 4;
			} else if (fmt[i+1] == '8') {
				size += tabsize * 8;
			} else {
				eprintf ("Invalid n format.\n");
				free (o);
				free (args);
				return -2;
			}
			i++;
			break;
		case 'D':
		case 'T':
		case 'u':
			//TODO complete this.
		default:
			//idx--; //Does this makes sense?
			break;
		}
		idx++;
		if (mode & R_PRINT_UNIONMODE) {
			if (size > biggest) {
				biggest = size;
			}
			size = 0;
		}
	}
	size *= times;
	free (o);
	free (args);
	return (mode & R_PRINT_UNIONMODE)? biggest : size;
}