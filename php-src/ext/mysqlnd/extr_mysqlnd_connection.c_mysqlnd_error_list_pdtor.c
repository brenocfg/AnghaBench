#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ error; } ;
typedef  TYPE_1__ MYSQLND_ERROR_LIST_ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_VOID_RETURN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mnd_pefree (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mysqlnd_error_list_pdtor(void * pDest)
{
	MYSQLND_ERROR_LIST_ELEMENT * element = (MYSQLND_ERROR_LIST_ELEMENT *) pDest;

	DBG_ENTER("mysqlnd_error_list_pdtor");
	if (element->error) {
		mnd_pefree(element->error, TRUE);
	}
	DBG_VOID_RETURN;
}