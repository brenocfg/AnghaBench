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
struct scsi_device_handler {int dummy; } ;

/* Variables and functions */
 struct scsi_device_handler* __scsi_dh_lookup (char const*) ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct scsi_device_handler *scsi_dh_lookup(const char *name)
{
	struct scsi_device_handler *dh;

	if (!name || strlen(name) == 0)
		return NULL;

	dh = __scsi_dh_lookup(name);
	if (!dh) {
		request_module("scsi_dh_%s", name);
		dh = __scsi_dh_lookup(name);
	}

	return dh;
}