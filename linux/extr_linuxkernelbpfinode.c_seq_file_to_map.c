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
struct seq_file {int /*<<< orphan*/  file; } ;
struct bpf_map {int dummy; } ;
struct TYPE_2__ {struct bpf_map* i_private; } ;

/* Variables and functions */
 TYPE_1__* file_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bpf_map *seq_file_to_map(struct seq_file *m)
{
	return file_inode(m->file)->i_private;
}