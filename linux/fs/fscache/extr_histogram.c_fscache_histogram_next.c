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
struct seq_file {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int HZ ; 

__attribute__((used)) static void *fscache_histogram_next(struct seq_file *m, void *v, loff_t *pos)
{
	(*pos)++;
	return (unsigned long long)*pos > HZ + 2 ?
		NULL : (void *)(unsigned long) *pos;
}