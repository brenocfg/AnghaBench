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
struct update_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 int do_http_request (struct update_info*,char*,long*) ; 
 char* get_path (char const*,char const*) ; 

__attribute__((used)) static inline bool do_relative_http_request(struct update_info *info,
					    const char *url, const char *file)
{
	long response_code;
	char *full_url = get_path(url, file);
	bool success = do_http_request(info, full_url, &response_code);
	bfree(full_url);
	return success && response_code == 200;
}