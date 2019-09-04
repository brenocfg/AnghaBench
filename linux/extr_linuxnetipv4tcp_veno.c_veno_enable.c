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
struct veno {int doing_veno_now; int minrtt; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct veno* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static inline void veno_enable(struct sock *sk)
{
	struct veno *veno = inet_csk_ca(sk);

	/* turn on Veno */
	veno->doing_veno_now = 1;

	veno->minrtt = 0x7fffffff;
}