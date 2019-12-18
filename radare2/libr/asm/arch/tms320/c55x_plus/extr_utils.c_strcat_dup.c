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
typedef  int ut32 ;
typedef  int st32 ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 

char *strcat_dup(char *s1, char *s2, st32 n_free) {
	char *res;
	ut32 len_s1 = s1? strlen (s1) : 0;
	ut32 len_s2 = s2? strlen (s2) : 0;

	if (!(res = (char *)malloc (len_s1 + len_s2 + 1))) {
		return NULL;
	}
	if (len_s1 > 0) {
		memcpy (res, s1, len_s1);
	}
	if (len_s2 > 0) {
		memcpy (res + len_s1, s2, len_s2);
	}
	res[len_s1 + len_s2] = '\0';
	if (n_free == 1) {
		R_FREE (s1);
	} else if (n_free == 2) {
		R_FREE (s2);
	} else if (n_free == 3) {
		R_FREE (s1);
		R_FREE (s2);
	}
	return res;
}