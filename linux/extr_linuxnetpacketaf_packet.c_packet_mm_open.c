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
struct vm_area_struct {struct file* vm_file; } ;
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct file {struct socket* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  mapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* pkt_sk (struct sock*) ; 

__attribute__((used)) static void packet_mm_open(struct vm_area_struct *vma)
{
	struct file *file = vma->vm_file;
	struct socket *sock = file->private_data;
	struct sock *sk = sock->sk;

	if (sk)
		atomic_inc(&pkt_sk(sk)->mapped);
}