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
struct TYPE_2__ {scalar_t__ array; } ;
struct file_download_data {TYPE_1__ buffer; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int RTMP_SERVICES_FORMAT_VERSION ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 scalar_t__ astrcmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * obs_data_create_from_json (char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool confirm_service_file(void *param, struct file_download_data *file)
{
	if (astrcmpi(file->name, "services.json") == 0) {
		obs_data_t *data;
		int format_version;

		data = obs_data_create_from_json((char *)file->buffer.array);
		if (!data)
			return false;

		format_version = (int)obs_data_get_int(data, "format_version");
		obs_data_release(data);

		if (format_version != RTMP_SERVICES_FORMAT_VERSION)
			return false;
	}

	UNUSED_PARAMETER(param);
	return true;
}