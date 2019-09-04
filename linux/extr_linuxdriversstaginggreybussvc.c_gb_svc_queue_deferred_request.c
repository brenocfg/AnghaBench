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
struct gb_svc_deferred_request {int /*<<< orphan*/  work; struct gb_operation* operation; } ;
struct gb_svc {int /*<<< orphan*/  wq; } ;
struct gb_operation {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct gb_svc* gb_connection_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_operation_get (struct gb_operation*) ; 
 int /*<<< orphan*/  gb_svc_process_deferred_request ; 
 struct gb_svc_deferred_request* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_svc_queue_deferred_request(struct gb_operation *operation)
{
	struct gb_svc *svc = gb_connection_get_data(operation->connection);
	struct gb_svc_deferred_request *dr;

	dr = kmalloc(sizeof(*dr), GFP_KERNEL);
	if (!dr)
		return -ENOMEM;

	gb_operation_get(operation);

	dr->operation = operation;
	INIT_WORK(&dr->work, gb_svc_process_deferred_request);

	queue_work(svc->wq, &dr->work);

	return 0;
}