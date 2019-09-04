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
struct afs_net {int dummy; } ;

/* Variables and functions */
 struct afs_net* afs_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_file_single_net (struct seq_file*) ; 

__attribute__((used)) static inline struct afs_net *afs_seq2net_single(struct seq_file *m)
{
	return afs_net(seq_file_single_net(m));
}