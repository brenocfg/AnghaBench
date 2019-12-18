#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * b; } ;
typedef  TYPE_1__ guid_t ;
struct TYPE_5__ {int /*<<< orphan*/ * b; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__ srv_id_template ; 

__attribute__((used)) static bool is_valid_srv_id(const guid_t *id)
{
	return !memcmp(&id->b[4], &srv_id_template.b[4], sizeof(guid_t) - 4);
}