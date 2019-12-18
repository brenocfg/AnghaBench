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
struct intel_pt_decoder {int /*<<< orphan*/  last_ip; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_set_last_ip (struct intel_pt_decoder*) ; 

__attribute__((used)) static inline void intel_pt_set_ip(struct intel_pt_decoder *decoder)
{
	intel_pt_set_last_ip(decoder);
	decoder->ip = decoder->last_ip;
}