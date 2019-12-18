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
struct path {int /*<<< orphan*/  dentry; } ;
struct bpf_prog {int dummy; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;

/* Variables and functions */
 struct bpf_prog* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct bpf_prog*) ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 struct bpf_prog* __get_prog_inode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  d_backing_inode (int /*<<< orphan*/ ) ; 
 int kern_path (char const*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  touch_atime (struct path*) ; 

struct bpf_prog *bpf_prog_get_type_path(const char *name, enum bpf_prog_type type)
{
	struct bpf_prog *prog;
	struct path path;
	int ret = kern_path(name, LOOKUP_FOLLOW, &path);
	if (ret)
		return ERR_PTR(ret);
	prog = __get_prog_inode(d_backing_inode(path.dentry), type);
	if (!IS_ERR(prog))
		touch_atime(&path);
	path_put(&path);
	return prog;
}