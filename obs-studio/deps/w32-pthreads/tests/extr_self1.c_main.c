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
struct TYPE_3__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ pthread_self () ; 
 int /*<<< orphan*/  pthread_win32_process_attach_np () ; 
 int /*<<< orphan*/  pthread_win32_process_detach_np () ; 

int
main(int argc, char * argv[])
{
	/*
	 * This should always succeed unless the system has no
	 * resources (memory) left.
	 */
	pthread_t self;

#if defined(PTW32_STATIC_LIB) && !(defined(_MSC_VER) || defined(__MINGW32__))
	pthread_win32_process_attach_np();
#endif

	self = pthread_self();

	assert(self.p != NULL);

#if defined(PTW32_STATIC_LIB) && !(defined(_MSC_VER) || defined(__MINGW32__))
	pthread_win32_process_detach_np();
#endif
	return 0;
}