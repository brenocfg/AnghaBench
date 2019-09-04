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

/* Variables and functions */
 int /*<<< orphan*/  GT_DIR ; 
 int cpio_mkgeneric_line (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpio_mkdir_line(const char *line)
{
	return cpio_mkgeneric_line(line, GT_DIR);
}