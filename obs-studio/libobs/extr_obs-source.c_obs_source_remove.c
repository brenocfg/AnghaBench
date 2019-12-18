#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int removed; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_source_dosignal (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 

void obs_source_remove(obs_source_t *source)
{
	if (!obs_source_valid(source, "obs_source_remove"))
		return;

	if (!source->removed) {
		source->removed = true;
		obs_source_dosignal(source, "source_remove", "remove");
	}
}