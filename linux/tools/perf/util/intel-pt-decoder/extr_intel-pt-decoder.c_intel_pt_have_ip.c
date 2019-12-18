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
struct TYPE_2__ {int count; } ;
struct intel_pt_decoder {TYPE_1__ packet; scalar_t__ have_last_ip; } ;

/* Variables and functions */

__attribute__((used)) static inline bool intel_pt_have_ip(struct intel_pt_decoder *decoder)
{
	return decoder->packet.count &&
	       (decoder->have_last_ip || decoder->packet.count == 3 ||
		decoder->packet.count == 6);
}