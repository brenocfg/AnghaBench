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
typedef  int /*<<< orphan*/  pdo_dbh_t ;

/* Variables and functions */

__attribute__((used)) static int oci_handle_begin(pdo_dbh_t *dbh) /* {{{ */
{
	/* with Oracle, there is nothing special to be done */
	return 1;
}