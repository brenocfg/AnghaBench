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
struct inode {struct bpf_prog* i_private; int /*<<< orphan*/ * i_op; } ;
struct bpf_prog {int dummy; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 struct bpf_prog* ERR_PTR (int) ; 
 int /*<<< orphan*/  MAY_READ ; 
 int /*<<< orphan*/  bpf_map_iops ; 
 int /*<<< orphan*/  bpf_prog_get_ok (struct bpf_prog*,int*,int) ; 
 struct bpf_prog* bpf_prog_inc (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_iops ; 
 int inode_permission (struct inode*,int /*<<< orphan*/ ) ; 
 int security_bpf_prog (struct bpf_prog*) ; 

__attribute__((used)) static struct bpf_prog *__get_prog_inode(struct inode *inode, enum bpf_prog_type type)
{
	struct bpf_prog *prog;
	int ret = inode_permission(inode, MAY_READ);
	if (ret)
		return ERR_PTR(ret);

	if (inode->i_op == &bpf_map_iops)
		return ERR_PTR(-EINVAL);
	if (inode->i_op != &bpf_prog_iops)
		return ERR_PTR(-EACCES);

	prog = inode->i_private;

	ret = security_bpf_prog(prog);
	if (ret < 0)
		return ERR_PTR(ret);

	if (!bpf_prog_get_ok(prog, &type, false))
		return ERR_PTR(-EINVAL);

	return bpf_prog_inc(prog);
}