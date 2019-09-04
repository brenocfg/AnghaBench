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
typedef  int /*<<< orphan*/  MYSQL ;

/* Variables and functions */
 int /*<<< orphan*/  MYSQLI_CLOSE_IMPLICIT ; 
 int /*<<< orphan*/  mysqli_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void php_mysqli_dtor_p_elements(void *data)
{
	MYSQL *mysql = (MYSQL *)data;
	mysqli_close(mysql, MYSQLI_CLOSE_IMPLICIT);
}