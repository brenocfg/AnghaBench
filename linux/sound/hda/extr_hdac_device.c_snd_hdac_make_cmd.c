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
typedef  int u32 ;
struct hdac_device {int addr; int /*<<< orphan*/  dev; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int snd_hdac_make_cmd(struct hdac_device *codec, hda_nid_t nid,
				      unsigned int verb, unsigned int parm)
{
	u32 val, addr;

	addr = codec->addr;
	if ((addr & ~0xf) || (nid & ~0x7f) ||
	    (verb & ~0xfff) || (parm & ~0xffff)) {
		dev_err(&codec->dev, "out of range cmd %x:%x:%x:%x\n",
			addr, nid, verb, parm);
		return -1;
	}

	val = addr << 28;
	val |= (u32)nid << 20;
	val |= verb << 8;
	val |= parm;
	return val;
}