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
struct async_scan_data {struct Scsi_Host* shost; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_scsi_scan_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_finish_async_scan (struct async_scan_data*) ; 

__attribute__((used)) static void do_scan_async(void *_data, async_cookie_t c)
{
	struct async_scan_data *data = _data;
	struct Scsi_Host *shost = data->shost;

	do_scsi_scan_host(shost);
	scsi_finish_async_scan(data);
}