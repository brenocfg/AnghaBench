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
typedef  int /*<<< orphan*/  php_url ;

/* Variables and functions */
 int /*<<< orphan*/  php_url_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delete_url(void *handle) /* {{{ */
{
	php_url_free((php_url*)handle);
}