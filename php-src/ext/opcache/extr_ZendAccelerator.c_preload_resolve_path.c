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
typedef  int /*<<< orphan*/  zend_string ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 scalar_t__ is_stream_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_resolve_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_string *preload_resolve_path(zend_string *filename)
{
	if (is_stream_path(ZSTR_VAL(filename))) {
		return NULL;
	}
	return zend_resolve_path(ZSTR_VAL(filename), ZSTR_LEN(filename));
}