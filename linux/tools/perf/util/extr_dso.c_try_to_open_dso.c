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
struct machine {int dummy; } ;
struct TYPE_2__ {scalar_t__ fd; int /*<<< orphan*/  status; } ;
struct dso {int binary_type; TYPE_1__ data; } ;
typedef  enum dso_binary_type { ____Placeholder_dso_binary_type } dso_binary_type ;

/* Variables and functions */
 int DSO_BINARY_TYPE__BUILD_ID_CACHE ; 
 int DSO_BINARY_TYPE__NOT_FOUND ; 
 int DSO_BINARY_TYPE__SYSTEM_PATH_DSO ; 
 int /*<<< orphan*/  DSO_DATA_STATUS_ERROR ; 
 int /*<<< orphan*/  DSO_DATA_STATUS_OK ; 
 void* open_dso (struct dso*,struct machine*) ; 

__attribute__((used)) static void try_to_open_dso(struct dso *dso, struct machine *machine)
{
	enum dso_binary_type binary_type_data[] = {
		DSO_BINARY_TYPE__BUILD_ID_CACHE,
		DSO_BINARY_TYPE__SYSTEM_PATH_DSO,
		DSO_BINARY_TYPE__NOT_FOUND,
	};
	int i = 0;

	if (dso->data.fd >= 0)
		return;

	if (dso->binary_type != DSO_BINARY_TYPE__NOT_FOUND) {
		dso->data.fd = open_dso(dso, machine);
		goto out;
	}

	do {
		dso->binary_type = binary_type_data[i++];

		dso->data.fd = open_dso(dso, machine);
		if (dso->data.fd >= 0)
			goto out;

	} while (dso->binary_type != DSO_BINARY_TYPE__NOT_FOUND);
out:
	if (dso->data.fd >= 0)
		dso->data.status = DSO_DATA_STATUS_OK;
	else
		dso->data.status = DSO_DATA_STATUS_ERROR;
}