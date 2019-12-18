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
 char* strdup (char*) ; 

__attribute__((used)) static char *get_rp(const char *rtype) {
	char *rp = NULL;
	switch (rtype[0]) {
	case 'v':
		rp = strdup ("void");
		break;
	case 'c':
		rp = strdup ("char");
		break;
	case 'i':
		rp = strdup ("int");
		break;
	case 's':
		rp = strdup ("short");
		break;
	case 'l':
		rp = strdup ("long");
		break;
	case 'q':
		rp = strdup ("long long");
		break;
	case 'C':
		rp = strdup ("unsigned char");
		break;
	case 'I':
		rp = strdup ("unsigned int");
		break;
	case 'S':
		rp = strdup ("unsigned short");
		break;
	case 'L':
		rp = strdup ("unsigned long");
		break;
	case 'Q':
		rp = strdup ("unsigned long long");
		break;
	case 'f':
		rp = strdup ("float");
		break;
	case 'd':
		rp = strdup ("double");
		break;
	case 'D':
		rp = strdup ("long double");
		break;
	case 'B':
		rp = strdup ("bool");
		break;
	case '#':
		rp = strdup ("CLASS");
		break;
	default:
		rp = strdup ("unknown");
		break;
	}
	return rp;
}