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
struct nvme_ns_ids {int /*<<< orphan*/  eui64; int /*<<< orphan*/  nguid; int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 scalar_t__ memchr_inv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uuid_is_null (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nvme_ns_ids_valid(struct nvme_ns_ids *ids)
{
	return !uuid_is_null(&ids->uuid) ||
		memchr_inv(ids->nguid, 0, sizeof(ids->nguid)) ||
		memchr_inv(ids->eui64, 0, sizeof(ids->eui64));
}