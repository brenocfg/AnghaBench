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
struct TYPE_4__ {scalar_t__ handle; struct TYPE_4__* dirw; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int closedir(DIR *dp)
{/*{{{*/
	if (!dp)
		return 0;
	/* It is valid to scan an empty directory but we have an invalid
	   handle in this case (no first file found). */
	if (dp->handle != INVALID_HANDLE_VALUE) {
		FindClose(dp->handle);
	}
	if (dp->dirw)
		free(dp->dirw);
	if (dp)
		free(dp);

	return 0;
}