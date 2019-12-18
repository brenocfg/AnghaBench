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
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int wordpos(const char *esil, int n) {
	const char *w = esil;
	if (n < 1) {
		n = 0;
	}
	while (w && n--) {
		const char *nw = strchr (w + 1, ',');
		if (!nw) {
			return strlen (esil);
		}
		w = nw;
	}
	if (!w && n > 0) {
		return strlen (esil);
	}
	return (size_t)(w - esil);
}