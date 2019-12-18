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
typedef  int Size ;
typedef  TYPE_1__ DynamicFileList ;

/* Variables and functions */
 int add_size (int,scalar_t__) ; 
 TYPE_1__* file_list ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

Size
EstimateLibraryStateSpace(void)
{
	DynamicFileList *file_scanner;
	Size		size = 1;

	for (file_scanner = file_list;
		 file_scanner != NULL;
		 file_scanner = file_scanner->next)
		size = add_size(size, strlen(file_scanner->filename) + 1);

	return size;
}