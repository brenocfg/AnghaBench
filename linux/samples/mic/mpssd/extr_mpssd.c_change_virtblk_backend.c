#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int signaled; } ;
struct mic_info {TYPE_1__ mic_virtblk; struct mic_info* next; } ;
typedef  int /*<<< orphan*/  siginfo_t ;
struct TYPE_4__ {struct mic_info* next; } ;

/* Variables and functions */
 TYPE_2__ mic_list ; 

__attribute__((used)) static void
change_virtblk_backend(int x, siginfo_t *siginfo, void *p)
{
	struct mic_info *mic;

	for (mic = mic_list.next; mic != NULL; mic = mic->next)
		mic->mic_virtblk.signaled = 1/* true */;
}