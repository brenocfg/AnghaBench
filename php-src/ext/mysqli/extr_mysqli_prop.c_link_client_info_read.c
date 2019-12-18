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
typedef  int /*<<< orphan*/  mysqli_object ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MYSQLI_STATUS_INITIALIZED ; 
 int /*<<< orphan*/  MYSQL_SERVER_VERSION ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval *link_client_info_read(mysqli_object *obj, zval *retval)
{
	CHECK_STATUS(MYSQLI_STATUS_INITIALIZED);
	ZVAL_STRING(retval, MYSQL_SERVER_VERSION);
	return retval;
}