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
struct hdac_ext_stream {int /*<<< orphan*/  pplc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZX_PPLCCTL_RUN ; 
 int /*<<< orphan*/  AZX_REG_PPLCCTL ; 
 int /*<<< orphan*/  snd_hdac_updatel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void snd_hdac_ext_link_stream_clear(struct hdac_ext_stream *stream)
{
	snd_hdac_updatel(stream->pplc_addr, AZX_REG_PPLCCTL, AZX_PPLCCTL_RUN, 0);
}