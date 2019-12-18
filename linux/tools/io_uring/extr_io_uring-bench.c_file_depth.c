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
struct submitter {int nr_files; } ;

/* Variables and functions */
 int DEPTH ; 

__attribute__((used)) static unsigned file_depth(struct submitter *s)
{
	return (DEPTH + s->nr_files - 1) / s->nr_files;
}