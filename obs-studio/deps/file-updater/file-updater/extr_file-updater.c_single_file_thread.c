#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  da; int /*<<< orphan*/ * array; } ;
struct update_info {TYPE_1__ file_data; int /*<<< orphan*/  param; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,struct file_download_data*) ;int /*<<< orphan*/  url; int /*<<< orphan*/  curl; } ;
struct TYPE_4__ {int /*<<< orphan*/  da; } ;
struct file_download_data {TYPE_2__ buffer; scalar_t__ version; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  curl_easy_init () ; 
 int /*<<< orphan*/  do_http_request (struct update_info*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct file_download_data*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void *single_file_thread(void *data)
{
	struct update_info *info = data;
	struct file_download_data download_data;
	long response_code;

	info->curl = curl_easy_init();
	if (!info->curl) {
		warn("Could not initialize Curl");
		return NULL;
	}

	if (!do_http_request(info, info->url, &response_code))
		return NULL;
	if (!info->file_data.array || !info->file_data.array[0])
		return NULL;

	download_data.name = info->url;
	download_data.version = 0;
	download_data.buffer.da = info->file_data.da;
	info->callback(info->param, &download_data);
	info->file_data.da = download_data.buffer.da;
	return NULL;
}