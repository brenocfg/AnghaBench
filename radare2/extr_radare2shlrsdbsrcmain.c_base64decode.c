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
typedef  char ut8 ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* sdb_decode (char*,int*) ; 
 scalar_t__ stdin_slurp (int*) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static int base64decode() {
	ut8 *out;
	int len, ret = 1;
	char *in = (char *) stdin_slurp (&len);
	if (in) {
		out = sdb_decode (in, &len);
		if (out) {
			if (len >= 0) {
				write (1, out, len);
				ret = 0;
			}
			free (out);
		}
		free (in);
	}
	return ret;
}