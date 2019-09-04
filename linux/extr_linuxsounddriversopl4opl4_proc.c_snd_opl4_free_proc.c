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
struct snd_opl4 {int /*<<< orphan*/  proc_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_info_free_entry (int /*<<< orphan*/ ) ; 

void snd_opl4_free_proc(struct snd_opl4 *opl4)
{
	snd_info_free_entry(opl4->proc_entry);
}