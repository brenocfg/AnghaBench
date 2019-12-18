#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ctx ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_1__ CONTEXT ;

/* Variables and functions */
 int R_MIN (int,int) ; 
 int SetThreadContext (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 

__attribute__((used)) static int __set_thread_context(HANDLE th, const ut8 *buf, int size, int bits) {
	bool ret;
	CONTEXT ctx = {0};
	size = R_MIN (size, sizeof (ctx));
	memcpy (&ctx, buf, size);
	if(!(ret = SetThreadContext (th, &ctx))) {
		r_sys_perror ("__set_thread_context/SetThreadContext");
	}
	return ret;
}