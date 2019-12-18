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

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 int strlen (char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int parse_registerpair(const char *operand) {
	int res = -1;
	char *first, *second, *op;
	int fnum, snum;

	op = strdup (operand);
	first = strtok (op, ":");

	if (!first || strlen (first) < 2) {
		free (op);
		return -1;
	}

	second = strtok (NULL, ":");

	/* the next code handles two possible different representation of pair
	   by pair rx+1:rx
	   or by even register rx
	   this is a bit ugly, code-duplicating, however stable
	   anyway FIXME if you have better idea */
	if (second && strlen (second) < 2) {
		/* the pair is set by pair
		   this is currently useless, cause rasm2 filters ':' from assembler
		   however, this bug soon will be fixed */
		if (first[0] == 'r' && second[0] == 'r') {
			fnum = atoi(first+1);
			snum = atoi(second+1);
			if (fnum > snum && snum >= 0 && snum <= 30) {
				res = snum / 2;
			}
		} else if (first[0] >= 'x' && first[0] <= 'z'
			 && second[0] >= 'x' && second[0] <= 'z'
			 && first[1] == 'h' && second[1] == 'l') {
			// convert to register pair number by inversing and invert (and adding 12)
			res = (2 - ('z' - first[0])) + 12;
		}
	} else {
		// the pair by even register (first)
		if (first[0] == 'r') {
			snum = atoi(first+1);
			if (snum >= 0 && snum <= 30) {
				res = snum / 2;
			}
		} else if (first[0] >= 'x' && first[0] <= 'z') {
			res = (2 - ('z' - first[0])) + 12;
		}
	}
	free (op);
	return res;
}