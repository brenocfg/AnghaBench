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
struct fpgaimage {int /*<<< orphan*/  lendata; int /*<<< orphan*/  time; int /*<<< orphan*/  date; int /*<<< orphan*/  part; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gs_print_header(struct fpgaimage *fimage)
{
	pr_info("file: %s\n", fimage->filename);
	pr_info("part: %s\n", fimage->part);
	pr_info("date: %s\n", fimage->date);
	pr_info("time: %s\n", fimage->time);
	pr_info("lendata: %d\n", fimage->lendata);
}