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
struct azx_dev {int dummy; } ;
struct azx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  azx_stream (struct azx_dev*) ; 
 unsigned int snd_hdac_stream_get_pos_posbuf (int /*<<< orphan*/ ) ; 

unsigned int azx_get_pos_posbuf(struct azx *chip, struct azx_dev *azx_dev)
{
	return snd_hdac_stream_get_pos_posbuf(azx_stream(azx_dev));
}