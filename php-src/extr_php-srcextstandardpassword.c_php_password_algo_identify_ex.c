#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_5__ {int /*<<< orphan*/  (* valid ) (int /*<<< orphan*/  const*) ;} ;
typedef  TYPE_1__ php_password_algo ;

/* Variables and functions */
 int /*<<< orphan*/ * php_password_algo_extract_ident (int /*<<< orphan*/  const*) ; 
 TYPE_1__* php_password_algo_find (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

const php_password_algo* php_password_algo_identify_ex(const zend_string* hash, const php_password_algo *default_algo) {
	const php_password_algo *algo;
	zend_string *ident = php_password_algo_extract_ident(hash);

	if (!ident) {
		return default_algo;
	}

	algo = php_password_algo_find(ident);
	zend_string_release(ident);
	return (!algo || (algo->valid && !algo->valid(hash))) ? default_algo : algo;
}