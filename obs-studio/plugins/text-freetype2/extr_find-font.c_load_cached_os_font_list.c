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
typedef  int /*<<< orphan*/  ver ;
typedef  scalar_t__ uint32_t ;
struct serializer {int dummy; } ;
typedef  int /*<<< orphan*/  old_checksum ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  file_input_serializer_free (struct serializer*) ; 
 int file_input_serializer_init (struct serializer*,char*) ; 
 scalar_t__ font_cache_ver ; 
 scalar_t__ get_font_checksum () ; 
 int load_cached_font_list (struct serializer*) ; 
 char* obs_module_config_path (char*) ; 
 int read_data (struct serializer*,scalar_t__*,int) ; 
 int s_read (struct serializer*,scalar_t__*,int) ; 

bool load_cached_os_font_list(void)
{
	char *file_name = obs_module_config_path("font_data.bin");
	uint32_t old_checksum;
	uint32_t new_checksum;
	struct serializer s;
	uint32_t ver;
	bool success;

	success = file_input_serializer_init(&s, file_name);
	bfree(file_name);

	if (!success)
		return false;

	success = read_data(&s, &ver, sizeof(ver));

	if (!success || ver != font_cache_ver) {
		success = false;
		goto finish;
	}

	success = s_read(&s, &old_checksum, sizeof(old_checksum));
	new_checksum = get_font_checksum();

	if (!success || old_checksum != new_checksum) {
		success = false;
		goto finish;
	}

	success = load_cached_font_list(&s);

finish:
	file_input_serializer_free(&s);
	return success;
}