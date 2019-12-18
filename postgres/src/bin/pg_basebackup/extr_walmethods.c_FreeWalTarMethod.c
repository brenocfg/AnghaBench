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
struct TYPE_3__ {struct TYPE_3__* zlibOut; scalar_t__ compression; struct TYPE_3__* tarfilename; } ;

/* Variables and functions */
 int /*<<< orphan*/  pg_free (TYPE_1__*) ; 
 TYPE_1__* tar_data ; 

void
FreeWalTarMethod(void)
{
	pg_free(tar_data->tarfilename);
#ifdef HAVE_LIBZ
	if (tar_data->compression)
		pg_free(tar_data->zlibOut);
#endif
	pg_free(tar_data);
}