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
typedef  int /*<<< orphan*/  w3 ;
typedef  int /*<<< orphan*/  w2 ;
typedef  int /*<<< orphan*/  w1 ;
typedef  int /*<<< orphan*/  w0 ;
struct TYPE_3__ {char* retleave_asm; } ;
typedef  TYPE_1__ RParse ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  r_snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  r_str_ncpy (char*,char*,int) ; 
 int /*<<< orphan*/  replace (int,char**,char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static int parse (RParse *p, const char *data, char *str) {
	char w0[256], w1[256], w2[256], w3[256];
	int i;
	size_t len = strlen (data);
	int sz = 32;
	char *buf, *ptr, *optr, *end;
	if (len >= sizeof (w0) || sz >= sizeof (w0)) {
		return false;
	}
	// strdup can be slow here :?
	if (!(buf = strdup (data))) {
		return false;
	}
	*w0 = *w1 = *w2 = *w3 = '\0';
	if (*buf) {
		end = strchr (buf, '\0');
		ptr = strchr (buf, ' ');
		if (!ptr) {
			ptr = strchr (buf, '\t');
		}
		if (!ptr) {
			ptr = end;
		}
		*ptr = '\0';
		if (ptr != end) {
			for (++ptr; *ptr == ' '; ptr++) {
				;
			}
		}
		r_str_ncpy (w0, buf, sizeof (w0));
		r_str_ncpy (w1, ptr, sizeof (w1));
		optr = ptr;
		ptr = strchr (ptr, ',');
		if (ptr) {
			*ptr = '\0';
			for (++ptr; *ptr == ' '; ptr++) {
				;
			}
			r_str_ncpy (w1, optr, sizeof (w1));
			r_str_ncpy (w2, ptr, sizeof (w2));
			optr = ptr;
			ptr = strchr (ptr, ',');
			if (ptr) {
				*ptr = '\0';
				for (++ptr; *ptr == ' '; ptr++) {
					;
				}
				r_str_ncpy (w2, optr, sizeof (w2));
				r_str_ncpy (w3, ptr, sizeof (w3));
			}
		}
	}
	char *wa[] = { w0, w1, w2, w3 };
	int nw = 0;
	for (i = 0; i < 4; i++) {
		if (wa[i][0] != '\0') {
			nw++;
		}
	}
	/* TODO: interpretation of memory location fails*/
	//ensure imul & mul interpretations works
	if (strstr (w0, "mul")) {
		if (nw == 2)
		{
			r_str_ncpy (wa[3], wa[1], sizeof (w3));

			switch (wa[3][0]) {
			case 'q':
			case 'r': //qword, r..
				r_str_ncpy (wa[1], "rax", sizeof (w1));
				r_str_ncpy (wa[2], "rax", sizeof (w2));
				break;
			case 'd':
			case 'e': //dword, e..
				if (strlen (wa[3]) > 2) {
					r_str_ncpy (wa[1], "eax", sizeof (w1));
					r_str_ncpy (wa[2], "eax", sizeof (w2));
					break;
				}
			default : // .x, .p, .i or word
				if (wa[3][1] == 'x' || wa[3][1] == 'p' || \
					wa[3][1] == 'i' || wa[3][0] == 'w') {
					r_str_ncpy (wa[1], "ax", sizeof (w1));
					r_str_ncpy (wa[2], "ax", sizeof (w2));
				} else { // byte and lowest 8 bit registers
					r_str_ncpy (wa[1], "al", sizeof (w1));
					r_str_ncpy (wa[2], "al", sizeof (w2));
				}
			}
		}
		else if (nw == 3)
		{
			r_str_ncpy (wa[3], wa[2], sizeof (w3));
			r_str_ncpy (wa[2], wa[1], sizeof (w2));
		}

		replace (nw, wa, str);

	} else if ((strstr (w1, "ax") || strstr (w1, "ah") || strstr (w1, "al")) && !p->retleave_asm) {
		if (!(p->retleave_asm = (char *) malloc (sz))) {
			return false;
		}
		r_snprintf (p->retleave_asm, sz, "return %s", w2);
		replace (nw, wa, str);
	} else if ((strstr (w0, "leave") && p->retleave_asm) || (strstr (w0, "pop") && strstr (w1, "bp"))) {
		r_str_ncpy (wa[0], " \0", 2);
		r_str_ncpy (wa[1], " \0", 2);
		replace (nw, wa, str);
	} else if (strstr (w0, "ret") && p->retleave_asm) {
		r_str_ncpy (str, p->retleave_asm, sz);
		R_FREE (p->retleave_asm);
	} else if (p->retleave_asm) {
		R_FREE (p->retleave_asm);
		replace (nw, wa, str);
	} else {
		replace (nw, wa, str);
	}
	free (buf);
	return true;
}