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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  RAsmOp ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  r_asm_op_set_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,int*,int*) ; 

__attribute__((used)) static inline int r_asm_pseudo_fill(RAsmOp *op, char *input) {
	int i, repeat = 0, size=0, value=0;
	sscanf (input, "%d,%d,%d", &repeat, &size, &value); // use r_num?
	size *= (sizeof (value) * repeat);
	if (size > 0) {
		ut8 *buf = malloc (size);
		for (i = 0; i < size; i+= sizeof(value)) {
			memcpy (&buf[i], &value, sizeof(value));
		}
		r_asm_op_set_buf (op, buf, size);
		free (buf);
	} else {
		size = 0;
	}
	return size;
}