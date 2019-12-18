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
 int indexed ; 
 char const* indexjmp ; 
 int indx (char const**,char const**,int,char const**) ; 
 int ldH ; 
 int ldHL ; 
 int ldIX ; 
 int ldIY ; 
 int ld_HL ; 
 int ld_IX ; 
 int ld_IY ; 
 int ld_NN ; 
 char const* readword ; 

__attribute__((used)) static int rd_ld(const char **p) {
#define ldBC    1
#define ldDE    2
#define ldHL    3
#define ldSP    4
#define ldIX    5
#define ldIY    6
#define ldB     7
#define ldC     8
#define ldD     9
#define ldE     10
#define ldH     11
#define ldL     12
#define ld_HL   13
#define ldA     14
#define ldI     15
#define ldR     16
#define ld_BC   17
#define ld_DE   18
#define ld_IX   19
#define ld_IY   20
#define ld_NN   21
	int i;
	const char *list[] = {
		"ixh", "ixl", "iyh", "iyl", "bc", "de", "hl", "sp", "ix",
		"iy", "b", "c", "d", "e", "h", "l", "( hl )", "a", "i",
		"r", "( bc )", "( de )", "( ix +)", "(iy +)", "(*)", NULL
	};
	const char *nn;
	i = indx (p, list, 1, &nn);
	if (!i) {
		return 0;
	}
	if (i <= 2) {
		indexed = 0xdd;
		return ldH + (i == 2);
	}
	if (i <= 4) {
		indexed = 0xfd;
		return ldH + (i == 4);
	}
	i -= 4;
	if (i == ldIX || i == ldIY) {
		indexed = i == ldIX? 0xDD: 0xFD;
		return ldHL;
	}
	if (i == ld_IX || i == ld_IY) {
		indexjmp = nn;
		indexed = i == ld_IX? 0xDD: 0xFD;
		return ld_HL;
	}
	if (i == ld_NN) {
		readword = nn;
	}
	return i;
}