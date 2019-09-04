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

/* Variables and functions */
 scalar_t__ allowed_clients ; 
 int /*<<< orphan*/  fcgi_mgmt_vars ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ is_fastcgi ; 
 scalar_t__ is_initialized ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ *) ; 

void fcgi_shutdown(void)
{
	if (is_initialized) {
		zend_hash_destroy(&fcgi_mgmt_vars);
	}
	is_fastcgi = 0;
	if (allowed_clients) {
		free(allowed_clients);
	}
}