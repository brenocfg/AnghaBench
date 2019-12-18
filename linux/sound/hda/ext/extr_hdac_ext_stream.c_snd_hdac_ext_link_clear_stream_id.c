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
struct hdac_ext_link {int /*<<< orphan*/  ml_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZX_REG_ML_LOSIDV ; 
 int /*<<< orphan*/  snd_hdac_updatew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void snd_hdac_ext_link_clear_stream_id(struct hdac_ext_link *link,
				 int stream)
{
	snd_hdac_updatew(link->ml_addr, AZX_REG_ML_LOSIDV, (1 << stream), 0);
}