#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ Bucket ;

/* Variables and functions */
 int string_compare_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phpdbg_array_data_compare(const void *a, const void *b) {
	Bucket *f, *s;
	int result;
	zval *first, *second;

	f = *((Bucket **) a);
	s = *((Bucket **) b);

	first = &f->val;
	second = &s->val;

	result = string_compare_function(first, second);

	if (result < 0) {
		return -1;
	} else if (result > 0) {
		return 1;
	}

	return 0;
}