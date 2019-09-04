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
 char* r_str_ndup (char*,scalar_t__) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void esil_split_flg (char *esil_str, char **esil_main, char **esil_flg) {
	char *split = strstr (esil_str, "f,=");
	const int kCommaHits = 2;
	int hits = 0;

	if (split) {
		while (hits != kCommaHits) {
			--split;
			if (*split == ',') {
				hits++;
			}
		}
		*esil_flg = strdup (++split);
		*esil_main = r_str_ndup (esil_str, strlen (esil_str) - strlen (*esil_flg) - 1);
	}
}