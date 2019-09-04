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
struct fw_request {int disabled; int /*<<< orphan*/  node; } ;
struct fw_download {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_fw_req (struct fw_request*) ; 

__attribute__((used)) static void free_firmware(struct fw_download *fw_download,
			  struct fw_request *fw_req)
{
	/* Already disabled from timeout handlers */
	if (fw_req->disabled)
		return;

	mutex_lock(&fw_download->mutex);
	list_del(&fw_req->node);
	mutex_unlock(&fw_download->mutex);

	fw_req->disabled = true;
	put_fw_req(fw_req);
}