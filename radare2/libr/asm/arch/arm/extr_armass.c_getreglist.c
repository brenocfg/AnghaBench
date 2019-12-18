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
typedef  int st32 ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int getlistmask (char*) ; 
 int /*<<< orphan*/  r_str_endswith (char const*,char*) ; 
 char* r_str_ndup (char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static st32 getreglist(const char *input) {
	st32 res;
	
	if (!input || (strlen (input) < 2) || (*input != '{') || !r_str_endswith (input, "}")) {
		return -1;
	}
	if (*input) {
		input++;
	}
	char *temp = r_str_ndup (input, strlen (input) - 1);
	if (!temp) {
		return -1;
	}
	res = getlistmask (temp);
	free (temp);
	return res;
}