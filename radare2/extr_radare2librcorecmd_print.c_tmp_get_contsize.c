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
typedef  int ut32 ;
typedef  int /*<<< orphan*/  RAnalFunction ;

/* Variables and functions */
 int r_anal_fcn_contsize (int /*<<< orphan*/ *) ; 
 int r_anal_fcn_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut32 tmp_get_contsize(RAnalFunction *f) {
	int size = r_anal_fcn_contsize (f);
	size = (size > 0)? size: r_anal_fcn_size (f);
	return (size < 0)? 0: size;
}