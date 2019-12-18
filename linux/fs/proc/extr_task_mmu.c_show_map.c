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

/* Variables and functions */
 int /*<<< orphan*/  m_cache_vma (struct seq_file*,void*) ; 
 int /*<<< orphan*/  show_map_vma (struct seq_file*,void*) ; 

__attribute__((used)) static int show_map(struct seq_file *m, void *v)
{
	show_map_vma(m, v);
	m_cache_vma(m, v);
	return 0;
}