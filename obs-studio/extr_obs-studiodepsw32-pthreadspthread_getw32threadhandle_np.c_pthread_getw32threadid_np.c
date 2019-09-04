#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ ptw32_thread_t ;
struct TYPE_5__ {scalar_t__ p; } ;
typedef  TYPE_2__ pthread_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */

DWORD
pthread_getw32threadid_np (pthread_t thread)
{
  return ((ptw32_thread_t *)thread.p)->thread;
}