#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_8__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ mysqli_object ;
struct TYPE_10__ {int /*<<< orphan*/  status; scalar_t__ ptr; } ;
struct TYPE_9__ {scalar_t__ mysql; } ;
typedef  TYPE_2__ MY_MYSQL ;
typedef  TYPE_3__ MYSQLI_RESOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  MYSQLI_CLOSE_EXPLICIT ; 
 int /*<<< orphan*/  MYSQLI_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  efree (TYPE_2__*) ; 
 int /*<<< orphan*/  mysqli_objects_free_storage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_clear_mysql (TYPE_2__*) ; 
 int /*<<< orphan*/  php_mysqli_close (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* php_mysqli_fetch_object (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mysqli_link_free_storage(zend_object *object)
{
	mysqli_object 	*intern = php_mysqli_fetch_object(object);
	MYSQLI_RESOURCE	*my_res = (MYSQLI_RESOURCE *)intern->ptr;

	if (my_res && my_res->ptr) {
		MY_MYSQL *mysql = (MY_MYSQL *)my_res->ptr;
		if (mysql->mysql) {
			php_mysqli_close(mysql, MYSQLI_CLOSE_EXPLICIT, my_res->status);
		}
		php_clear_mysql(mysql);
		efree(mysql);
		my_res->status = MYSQLI_STATUS_UNKNOWN;
	}
	mysqli_objects_free_storage(object);
}