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
 scalar_t__ IS_ARRAY ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_assoc_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
enumerate_providers_fn (const char * const name,
                        const char * const desc,
                        const char * const file,
                        void * ud) /* {{{ */
{
	zval *zdesc = (zval *) ud;
	zval tmp_array;

	array_init(&tmp_array);

	add_assoc_string(&tmp_array, "name", (char *)name);
	add_assoc_string(&tmp_array, "desc", (char *)desc);
	add_assoc_string(&tmp_array, "file", (char *)file);

	if (Z_TYPE_P(zdesc)!=IS_ARRAY) {
		array_init(zdesc);
	}

	add_next_index_zval(zdesc, &tmp_array);
}