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
struct db_export {int dummy; } ;

/* Variables and functions */
 int db_export__deferred (struct db_export*) ; 

int db_export__flush(struct db_export *dbe)
{
	return db_export__deferred(dbe);
}