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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct pn533 {int dummy; } ;
typedef  int /*<<< orphan*/  pn533_send_async_complete_t ;

/* Variables and functions */
 int __pn533_send_async (struct pn533*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int pn533_send_data_async(struct pn533 *dev, u8 cmd_code,
				 struct sk_buff *req,
				 pn533_send_async_complete_t complete_cb,
				 void *complete_cb_context)
{
	int rc;

	rc = __pn533_send_async(dev, cmd_code, req, complete_cb,
				complete_cb_context);

	return rc;
}