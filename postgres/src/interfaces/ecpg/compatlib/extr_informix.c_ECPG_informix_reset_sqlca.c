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
struct sqlca_t {int dummy; } ;

/* Variables and functions */
 struct sqlca_t* ECPGget_sqlca () ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  sqlca_init ; 

void
ECPG_informix_reset_sqlca(void)
{
	struct sqlca_t *sqlca = ECPGget_sqlca();

	if (sqlca == NULL)
		return;

	memcpy((char *) sqlca, (char *) &sqlca_init, sizeof(struct sqlca_t));
}