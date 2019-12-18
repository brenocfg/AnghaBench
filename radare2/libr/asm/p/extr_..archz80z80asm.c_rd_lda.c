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
 int indx (char const**,char const**,int /*<<< orphan*/ ,char const**) ; 
 char const* readbyte ; 
 char const* readword ; 
 int writebyte ; 

__attribute__((used)) static int rd_lda(const char **p) {
#define A_N 7
#define A_I 9
#define A_R 10
#define A_NN 11
	int i;
	const char *list[] = {
		"( sp )", "( iy +)", "( de )", "( bc )", "( ix +)", "b", "c", "d", "e", "h",
		"l", "( hl )", "a", "i", "r", "(*)", "*", NULL
	};
	const char *nn;
	i = indx (p, list, 0, &nn);
	if (i == 2 || i == 5) {
		indexed = (i == 2)? 0xFD: 0xDD;
		indexjmp = nn;
		return 7;
	}
	if (i == 17) {
		readbyte = nn;
		writebyte = 1;
		return 7;
	}
	if (i == 16) {
		readword = nn;
	}
	return i - 5;
}