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
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  cs ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int pthread_attr_setaffinity_np (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int main(void)
{
	int ret = 0;
	pthread_attr_t thread_attr;
	cpu_set_t cs;

	pthread_attr_init(&thread_attr);
	CPU_ZERO(&cs);

	ret = pthread_attr_setaffinity_np(&thread_attr, sizeof(cs), &cs);

	return ret;
}