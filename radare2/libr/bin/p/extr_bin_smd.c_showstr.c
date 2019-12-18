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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_str_ndup (char const*,int) ; 

__attribute__((used)) static void showstr(const char *str, const ut8 *s, int len) {
	char *msg = r_str_ndup ((const char *) s, len);
	eprintf ("%s: %s\n", str, msg);
	free (msg);
}