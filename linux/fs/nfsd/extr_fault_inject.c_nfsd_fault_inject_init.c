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
typedef  int umode_t ;
struct nfsd_fault_inject_op {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct nfsd_fault_inject_op*) ; 
 int S_IFREG ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  debug_dir ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct nfsd_fault_inject_op*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_nfsd ; 
 struct nfsd_fault_inject_op* inject_ops ; 

void nfsd_fault_inject_init(void)
{
	unsigned int i;
	struct nfsd_fault_inject_op *op;
	umode_t mode = S_IFREG | S_IRUSR | S_IWUSR;

	debug_dir = debugfs_create_dir("nfsd", NULL);

	for (i = 0; i < ARRAY_SIZE(inject_ops); i++) {
		op = &inject_ops[i];
		debugfs_create_file(op->file, mode, debug_dir, op, &fops_nfsd);
	}
}