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
struct sock {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int tcp_sendpage_locked (struct sock*,struct page*,int,size_t,int) ; 

int tcp_sendpage(struct sock *sk, struct page *page, int offset,
		 size_t size, int flags)
{
	int ret;

	lock_sock(sk);
	ret = tcp_sendpage_locked(sk, page, offset, size, flags);
	release_sock(sk);

	return ret;
}