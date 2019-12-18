#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ R_PDB ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char*) ; 
 int r_buf_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_int_var(char *var_name, int *var, R_PDB *pdb) {
	if (var) {
		*var = 0;
	}
	int bytes_read = r_buf_read (pdb->buf, (ut8 *) var, 4);
	if (bytes_read != 4) {
		eprintf ("Error while reading from file '%s'\n", var_name);
		return 0;
	}
	return bytes_read;
}