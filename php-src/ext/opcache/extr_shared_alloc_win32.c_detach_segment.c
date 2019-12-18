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
typedef  int /*<<< orphan*/  zend_shared_segment ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mapping_base ; 
 int /*<<< orphan*/ * memfile ; 
 int /*<<< orphan*/ * memory_mutex ; 
 int /*<<< orphan*/  zend_shared_alloc_lock_win32 () ; 
 int /*<<< orphan*/  zend_shared_alloc_unlock_win32 () ; 

__attribute__((used)) static int detach_segment(zend_shared_segment *shared_segment)
{
	zend_shared_alloc_lock_win32();
	if (mapping_base) {
		UnmapViewOfFile(mapping_base);
		mapping_base = NULL;
	}
	CloseHandle(memfile);
	memfile = NULL;
	zend_shared_alloc_unlock_win32();
	CloseHandle(memory_mutex);
	memory_mutex = NULL;
	return 0;
}