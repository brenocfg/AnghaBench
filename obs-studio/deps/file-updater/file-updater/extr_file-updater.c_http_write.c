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
typedef  int /*<<< orphan*/  uint8_t ;
struct update_info {int /*<<< orphan*/  file_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static size_t http_write(uint8_t *ptr, size_t size, size_t nmemb,
			 struct update_info *info)
{
	size_t total = size * nmemb;
	if (total)
		da_push_back_array(info->file_data, ptr, total);

	return total;
}