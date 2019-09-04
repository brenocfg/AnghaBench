#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * tags; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tags; } ;
struct TYPE_7__ {int /*<<< orphan*/  url_adapt_output_hosts_ht; int /*<<< orphan*/  url_adapt_session_hosts_ht; TYPE_2__ url_adapt_output_ex; TYPE_1__ url_adapt_session_ex; } ;
typedef  TYPE_3__ php_basic_globals ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void basic_globals_dtor(php_basic_globals *basic_globals_p) /* {{{ */
{
	if (basic_globals_p->url_adapt_session_ex.tags) {
		zend_hash_destroy(basic_globals_p->url_adapt_session_ex.tags);
		free(basic_globals_p->url_adapt_session_ex.tags);
	}
	if (basic_globals_p->url_adapt_output_ex.tags) {
		zend_hash_destroy(basic_globals_p->url_adapt_output_ex.tags);
		free(basic_globals_p->url_adapt_output_ex.tags);
	}

	zend_hash_destroy(&basic_globals_p->url_adapt_session_hosts_ht);
	zend_hash_destroy(&basic_globals_p->url_adapt_output_hosts_ht);
}