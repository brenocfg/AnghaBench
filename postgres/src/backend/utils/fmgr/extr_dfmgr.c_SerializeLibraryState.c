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
struct TYPE_3__ {int /*<<< orphan*/  filename; struct TYPE_3__* next; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_1__ DynamicFileList ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__* file_list ; 
 scalar_t__ strlcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 

void
SerializeLibraryState(Size maxsize, char *start_address)
{
	DynamicFileList *file_scanner;

	for (file_scanner = file_list;
		 file_scanner != NULL;
		 file_scanner = file_scanner->next)
	{
		Size		len;

		len = strlcpy(start_address, file_scanner->filename, maxsize) + 1;
		Assert(len < maxsize);
		maxsize -= len;
		start_address += len;
	}
	start_address[0] = '\0';
}