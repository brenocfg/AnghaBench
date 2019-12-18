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
struct snd_sb_csp {int dummy; } ;
struct snd_hwdep {struct snd_sb_csp* private_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int snd_sb_csp_unuse (struct snd_sb_csp*) ; 

__attribute__((used)) static int snd_sb_csp_release(struct snd_hwdep * hw, struct file *file)
{
	struct snd_sb_csp *p = hw->private_data;
	return (snd_sb_csp_unuse(p));
}