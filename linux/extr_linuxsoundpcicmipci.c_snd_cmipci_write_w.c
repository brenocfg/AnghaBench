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
struct cmipci {scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 

__attribute__((used)) static inline void snd_cmipci_write_w(struct cmipci *cm, unsigned int cmd, unsigned short data)
{
	outw(data, cm->iobase + cmd);
}