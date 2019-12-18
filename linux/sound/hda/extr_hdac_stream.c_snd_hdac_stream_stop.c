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
struct hdac_stream {int index; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTCTL ; 
 int /*<<< orphan*/  snd_hdac_chip_updatel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_stream_clear (struct hdac_stream*) ; 
 int /*<<< orphan*/  trace_snd_hdac_stream_stop (int /*<<< orphan*/ ,struct hdac_stream*) ; 

void snd_hdac_stream_stop(struct hdac_stream *azx_dev)
{
	trace_snd_hdac_stream_stop(azx_dev->bus, azx_dev);

	snd_hdac_stream_clear(azx_dev);
	/* disable SIE */
	snd_hdac_chip_updatel(azx_dev->bus, INTCTL, 1 << azx_dev->index, 0);
}