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
typedef  int /*<<< orphan*/  Rangstr ;

/* Variables and functions */
 int /*<<< orphan*/  json_get (char const*,char const*) ; 
 char* rangstr_dup (int /*<<< orphan*/ *) ; 

char *api_json_get (const char *s, const char *p) {
	Rangstr rs = json_get (s, p);
	return rangstr_dup (&rs);
}