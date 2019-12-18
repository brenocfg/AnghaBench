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
struct TYPE_2__ {int /*<<< orphan*/  h_name; } ;
struct gethostbyname_data {int /*<<< orphan*/  addr_name; TYPE_1__ hostent_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static void gethostbyname_data_setstring(struct gethostbyname_data* data, char* name) {
	snprintf(data->addr_name, sizeof(data->addr_name), "%s", name);
	data->hostent_space.h_name = data->addr_name;
}