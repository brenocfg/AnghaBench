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

__attribute__((used)) static void php_enchant_list_dicts_fn( const char * const lang_tag,
	   	const char * const provider_name, const char * const provider_desc,
		const char * const provider_file, void * ud) /* {{{ */
{
	zval *zdesc = (zval *) ud;
	zval tmp_array;

	array_init(&tmp_array);
	add_assoc_string(&tmp_array, "lang_tag", (char *)lang_tag);
	add_assoc_string(&tmp_array, "provider_name", (char *)provider_name);
	add_assoc_string(&tmp_array, "provider_desc", (char *)provider_desc);
	add_assoc_string(&tmp_array, "provider_file", (char *)provider_file);

	if (Z_TYPE_P(zdesc) != IS_ARRAY) {
		array_init(zdesc);
	}
	add_next_index_zval(zdesc, &tmp_array);

}