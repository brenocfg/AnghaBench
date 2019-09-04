#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct enc_encoder {TYPE_1__* context; } ;
struct TYPE_2__ {size_t extradata_size; int /*<<< orphan*/ * extradata; } ;

/* Variables and functions */

__attribute__((used)) static bool enc_extra_data(void *data, uint8_t **extra_data, size_t *size)
{
	struct enc_encoder *enc = data;

	*extra_data = enc->context->extradata;
	*size       = enc->context->extradata_size;
	return true;
}