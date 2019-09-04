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

/* Variables and functions */
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pthread_exit (void*) ; 

void *
func(void * arg)
{
    int i = (int)(size_t)arg;

    Sleep(i * 100);

    pthread_exit(arg);

    /* Never reached. */
    exit(1);
}