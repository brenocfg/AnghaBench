#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_3__ {int /*<<< orphan*/  text; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_REJECT_DUPLICATES ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int RTMP_SERVICES_FORMAT_VERSION ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int get_int_val (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_incref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char*) ; 
 char* os_quick_read_utf8_file (char const*) ; 

__attribute__((used)) static json_t *open_json_file(const char *file)
{
	char *file_data = os_quick_read_utf8_file(file);
	json_error_t error;
	json_t *root;
	json_t *list;
	int format_ver;

	if (!file_data)
		return NULL;

	root = json_loads(file_data, JSON_REJECT_DUPLICATES, &error);
	bfree(file_data);

	if (!root) {
		blog(LOG_WARNING,
		     "rtmp-common.c: [open_json_file] "
		     "Error reading JSON file (%d): %s",
		     error.line, error.text);
		return NULL;
	}

	format_ver = get_int_val(root, "format_version");

	if (format_ver != RTMP_SERVICES_FORMAT_VERSION) {
		blog(LOG_DEBUG,
		     "rtmp-common.c: [open_json_file] "
		     "Wrong format version (%d), expected %d",
		     format_ver, RTMP_SERVICES_FORMAT_VERSION);
		json_decref(root);
		return NULL;
	}

	list = json_object_get(root, "services");
	if (list)
		json_incref(list);
	json_decref(root);

	if (!list) {
		blog(LOG_WARNING, "rtmp-common.c: [open_json_file] "
				  "No services list");
		return NULL;
	}

	return list;
}