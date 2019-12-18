#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_3__ {int a; int b; int c; int d; } ;
typedef  TYPE_1__ ranctx ;

/* Variables and functions */
 int rot (int,int) ; 

__attribute__((used)) static u64 ranval(ranctx *x) {
	u64 e = x->a - rot(x->b, 7);
	x->a = x->b ^ rot(x->c, 13);
	x->b = x->c + rot(x->d, 37);
	x->c = x->d + e;
	x->d = e + x->a;
	return x->d;
}