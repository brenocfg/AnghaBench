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
struct TYPE_2__ {int /*<<< orphan*/  files; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int __alloc_fd (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  rlimit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_fd(unsigned start, unsigned flags)
{
	return __alloc_fd(current->files, start, rlimit(RLIMIT_NOFILE), flags);
}