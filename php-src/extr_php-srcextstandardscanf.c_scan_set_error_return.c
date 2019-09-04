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
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_ERROR_EOF ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_null (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void scan_set_error_return(int numVars, zval *return_value) /* {{{ */
{
	if (numVars) {
		ZVAL_LONG(return_value, SCAN_ERROR_EOF);  /* EOF marker */
	} else {
		/* convert_to_null calls destructor */
		convert_to_null(return_value);
	}
}