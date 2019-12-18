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
struct snd_seq_oss_arg {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static int snd_opl3_reset_seq_oss(struct snd_seq_oss_arg *arg)
{
	if (snd_BUG_ON(!arg))
		return -ENXIO;

	return 0;
}