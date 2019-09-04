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
struct ff_demuxer {scalar_t__ abort; } ;

/* Variables and functions */

__attribute__((used)) static int demuxer_interrupted_callback(void *opaque)
{
	return opaque != NULL && ((struct ff_demuxer *)opaque)->abort;
}