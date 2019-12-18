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
struct file {int f_flags; } ;

/* Variables and functions */
 int O_DIRECT ; 

__attribute__((used)) static inline int is_packetized(struct file *file)
{
	return (file->f_flags & O_DIRECT) != 0;
}