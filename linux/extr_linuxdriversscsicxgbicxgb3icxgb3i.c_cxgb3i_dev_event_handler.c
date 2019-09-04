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
typedef  int /*<<< orphan*/  u32 ;
struct t3cdev {int dummy; } ;
struct cxgbi_device {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int CXGBI_DBG_TOE ; 
 int /*<<< orphan*/  CXGBI_FLAG_ADAPTER_RESET ; 
#define  OFFLOAD_STATUS_DOWN 129 
#define  OFFLOAD_STATUS_UP 128 
 struct cxgbi_device* cxgbi_device_find_by_lldev (struct t3cdev*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct t3cdev*,struct cxgbi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxgb3i_dev_event_handler(struct t3cdev *t3dev, u32 event, u32 port)
{
	struct cxgbi_device *cdev = cxgbi_device_find_by_lldev(t3dev);

	log_debug(1 << CXGBI_DBG_TOE,
		"0x%p, cdev 0x%p, event 0x%x, port 0x%x.\n",
		t3dev, cdev, event, port);
	if (!cdev)
		return;

	switch (event) {
	case OFFLOAD_STATUS_DOWN:
		cdev->flags |= CXGBI_FLAG_ADAPTER_RESET;
		break;
	case OFFLOAD_STATUS_UP:
		cdev->flags &= ~CXGBI_FLAG_ADAPTER_RESET;
		break;
	}
}