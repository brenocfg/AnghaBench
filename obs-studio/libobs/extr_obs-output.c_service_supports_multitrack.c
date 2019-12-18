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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int (* supports_multitrack ) (int /*<<< orphan*/ ) ;} ;
struct obs_service {TYPE_2__ context; TYPE_1__ info; } ;
struct obs_output {struct obs_service* service; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool service_supports_multitrack(const struct obs_output *output)
{
	const struct obs_service *service = output->service;

	if (!service || !service->info.supports_multitrack) {
		return false;
	}

	return service->info.supports_multitrack(service->context.data);
}