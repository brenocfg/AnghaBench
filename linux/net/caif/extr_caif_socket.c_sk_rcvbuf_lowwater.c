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
struct TYPE_2__ {int sk_rcvbuf; } ;
struct caifsock {TYPE_1__ sk; } ;

/* Variables and functions */

__attribute__((used)) static int sk_rcvbuf_lowwater(struct caifsock *cf_sk)
{
	/* A quarter of full buffer is used a low water mark */
	return cf_sk->sk.sk_rcvbuf / 4;
}