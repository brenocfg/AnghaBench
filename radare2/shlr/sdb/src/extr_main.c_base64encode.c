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
 int /*<<< orphan*/  puts (char*) ; 
 char* sdb_encode (char*,int) ; 
 scalar_t__ stdin_slurp (int*) ; 

__attribute__((used)) static int base64encode() {
	char *out;
	int len = 0;
	ut8 *in = (ut8 *) stdin_slurp (&len);
	if (!in) {
		return 0;
	}
	out = sdb_encode (in, len);
	if (!out) {
		free (in);
		return 1;
	}
	puts (out);
	free (out);
	free (in);
	return 0;
}