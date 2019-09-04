#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t frameLength; } ;
struct TYPE_4__ {TYPE_1__ info; } ;
typedef  TYPE_2__ libfdk_encoder_t ;

/* Variables and functions */

__attribute__((used)) static size_t libfdk_frame_size(void *data)
{
	libfdk_encoder_t *enc = data;

	return enc->info.frameLength;
}