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
 char* api_json_set (char const*,char const*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

char *api_json_seti (const char *s, const char *k, int a) {
	char str[64];
	sprintf (str, "%d", a);
	return api_json_set (s, k, str);
}