#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * sample_status; } ;
typedef  TYPE_1__ snd_wavefront_t ;

/* Variables and functions */
 int /*<<< orphan*/  WFC_DELETE_SAMPLE ; 
 int /*<<< orphan*/  WF_ST_EMPTY ; 
 int snd_wavefront_cmd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static int
wavefront_delete_sample (snd_wavefront_t *dev, int sample_num)

{
	unsigned char wbuf[2];
	int x;

	wbuf[0] = sample_num & 0x7f;
	wbuf[1] = sample_num >> 7;

	if ((x = snd_wavefront_cmd (dev, WFC_DELETE_SAMPLE, NULL, wbuf)) == 0) {
		dev->sample_status[sample_num] = WF_ST_EMPTY;
	}

	return x;
}