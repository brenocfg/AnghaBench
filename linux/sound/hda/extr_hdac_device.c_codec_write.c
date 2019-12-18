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
struct hdac_device {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int snd_hdac_exec_verb (struct hdac_device*,unsigned int,int,int /*<<< orphan*/ *) ; 
 unsigned int snd_hdac_make_cmd (struct hdac_device*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int codec_write(struct hdac_device *hdac, hda_nid_t nid,
			int flags, unsigned int verb, unsigned int parm)
{
	unsigned int cmd = snd_hdac_make_cmd(hdac, nid, verb, parm);

	return snd_hdac_exec_verb(hdac, cmd, flags, NULL);
}