#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * AHX; } ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  archive_close_connection ; 
 int /*<<< orphan*/  on_exit_nicely (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ shutdown_info ; 

void
on_exit_close_archive(Archive *AHX)
{
	shutdown_info.AHX = AHX;
	on_exit_nicely(archive_close_connection, &shutdown_info);
}