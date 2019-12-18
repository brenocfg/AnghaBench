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
struct persistent_ram_zone {TYPE_1__* buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 size_t atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline size_t buffer_size(struct persistent_ram_zone *prz)
{
	return atomic_read(&prz->buffer->size);
}