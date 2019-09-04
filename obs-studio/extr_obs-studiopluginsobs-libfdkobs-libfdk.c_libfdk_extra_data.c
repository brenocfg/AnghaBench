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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t confSize; int /*<<< orphan*/ * confBuf; } ;
struct TYPE_4__ {TYPE_1__ info; } ;
typedef  TYPE_2__ libfdk_encoder_t ;

/* Variables and functions */

__attribute__((used)) static bool libfdk_extra_data(void *data, uint8_t **extra_data, size_t *size)
{
	libfdk_encoder_t *enc = data;

	*size = enc->info.confSize;
	*extra_data = enc->info.confBuf;

	return true;
}