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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int (* get_sei_data ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ;} ;
struct obs_encoder {TYPE_2__ context; TYPE_1__ info; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 

__attribute__((used)) static inline bool get_sei(const struct obs_encoder *encoder, uint8_t **sei,
			   size_t *size)
{
	if (encoder->info.get_sei_data)
		return encoder->info.get_sei_data(encoder->context.data, sei,
						  size);
	return false;
}