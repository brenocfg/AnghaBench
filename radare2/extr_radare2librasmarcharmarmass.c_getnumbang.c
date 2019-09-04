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
typedef  int ut64 ;

/* Variables and functions */
 int err ; 
 int /*<<< orphan*/  free (char*) ; 
 int getnum (char*) ; 
 int /*<<< orphan*/  r_str_endswith (char const*,char*) ; 
 char* r_str_ndup (char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static ut64 getnumbang(const char *str) {
	ut64 res;

	if (!str || !*str || !r_str_endswith (str, "!")) {
		err = true;
		return 0;
	}
	char *temp = r_str_ndup (str, strlen (str) - 1);
	if (!temp) {
		return -1;
	}
	err = false;
	res = getnum (temp);
	free (temp);
	return res; // err propagates
}