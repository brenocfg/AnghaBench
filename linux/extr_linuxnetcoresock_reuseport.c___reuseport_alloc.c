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
struct sock_reuseport {unsigned int max_socks; int /*<<< orphan*/  prog; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sock_reuseport* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sock_reuseport *__reuseport_alloc(unsigned int max_socks)
{
	unsigned int size = sizeof(struct sock_reuseport) +
		      sizeof(struct sock *) * max_socks;
	struct sock_reuseport *reuse = kzalloc(size, GFP_ATOMIC);

	if (!reuse)
		return NULL;

	reuse->max_socks = max_socks;

	RCU_INIT_POINTER(reuse->prog, NULL);
	return reuse;
}