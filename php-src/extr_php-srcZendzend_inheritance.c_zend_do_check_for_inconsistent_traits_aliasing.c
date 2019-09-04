#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ method_name; } ;
struct TYPE_7__ {TYPE_1__ trait_method; scalar_t__ alias; } ;
typedef  TYPE_2__ zend_trait_alias ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_8__ {int /*<<< orphan*/  function_table; TYPE_2__** trait_aliases; } ;
typedef  TYPE_3__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int /*<<< orphan*/  ZSTR_VAL (scalar_t__) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ zend_hash_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_tolower (scalar_t__) ; 

__attribute__((used)) static void zend_do_check_for_inconsistent_traits_aliasing(zend_class_entry *ce, zend_class_entry **aliases) /* {{{ */
{
	int i = 0;
	zend_trait_alias* cur_alias;
	zend_string* lc_method_name;

	if (ce->trait_aliases) {
		while (ce->trait_aliases[i]) {
			cur_alias = ce->trait_aliases[i];
			/** The trait for this alias has not been resolved, this means, this
				alias was not applied. Abort with an error. */
			if (!aliases[i]) {
				if (cur_alias->alias) {
					/** Plain old inconsistency/typo/bug */
					zend_error_noreturn(E_COMPILE_ERROR,
							   "An alias (%s) was defined for method %s(), but this method does not exist",
							   ZSTR_VAL(cur_alias->alias),
							   ZSTR_VAL(cur_alias->trait_method.method_name));
				} else {
					/** Here are two possible cases:
						1) this is an attempt to modify the visibility
						   of a method introduce as part of another alias.
						   Since that seems to violate the DRY principle,
						   we check against it and abort.
						2) it is just a plain old inconsitency/typo/bug
						   as in the case where alias is set. */

					lc_method_name = zend_string_tolower(
						cur_alias->trait_method.method_name);
					if (zend_hash_exists(&ce->function_table,
										 lc_method_name)) {
						zend_string_release_ex(lc_method_name, 0);
						zend_error_noreturn(E_COMPILE_ERROR,
								   "The modifiers for the trait alias %s() need to be changed in the same statement in which the alias is defined. Error",
								   ZSTR_VAL(cur_alias->trait_method.method_name));
					} else {
						zend_string_release_ex(lc_method_name, 0);
						zend_error_noreturn(E_COMPILE_ERROR,
								   "The modifiers of the trait method %s() are changed, but this method does not exist. Error",
								   ZSTR_VAL(cur_alias->trait_method.method_name));

					}
				}
			}
			i++;
		}
	}
}