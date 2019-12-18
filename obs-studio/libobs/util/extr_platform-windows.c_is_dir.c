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
struct TYPE_3__ {int dwFileAttributes; } ;
typedef  TYPE_1__ WIN32_FIND_DATA ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 

__attribute__((used)) static inline bool is_dir(WIN32_FIND_DATA *wfd)
{
	return !!(wfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}