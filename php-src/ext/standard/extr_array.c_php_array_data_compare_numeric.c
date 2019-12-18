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
 scalar_t__ IS_INDIRECT ; 
 scalar_t__ UNEXPECTED (int) ; 
 int /*<<< orphan*/ * Z_INDIRECT_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int numeric_compare_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_array_data_compare_numeric(const void *a, const void *b) /* {{{ */
{
	Bucket *f;
	Bucket *s;
	zval *first;
	zval *second;

	f = (Bucket *) a;
	s = (Bucket *) b;

	first = &f->val;
	second = &s->val;

	if (UNEXPECTED(Z_TYPE_P(first) == IS_INDIRECT)) {
		first = Z_INDIRECT_P(first);
	}
	if (UNEXPECTED(Z_TYPE_P(second) == IS_INDIRECT)) {
		second = Z_INDIRECT_P(second);
	}

	return numeric_compare_function(first, second);
}