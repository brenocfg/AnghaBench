#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* data; } ;
typedef  TYPE_1__ MYSQLND_READ_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_VOID_RETURN ; 
 int /*<<< orphan*/  mnd_efree (TYPE_1__*) ; 

__attribute__((used)) static void
mysqlnd_read_buffer_free(MYSQLND_READ_BUFFER ** buffer)
{
	DBG_ENTER("mysqlnd_read_buffer_free");
	if (*buffer) {
		mnd_efree((*buffer)->data);
		mnd_efree(*buffer);
		*buffer = NULL;
	}
	DBG_VOID_RETURN;
}