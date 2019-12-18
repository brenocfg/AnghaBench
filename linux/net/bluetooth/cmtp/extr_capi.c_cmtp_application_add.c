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
struct cmtp_session {int /*<<< orphan*/  applications; } ;
struct cmtp_application {int /*<<< orphan*/  list; int /*<<< orphan*/  appl; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct cmtp_session*,struct cmtp_application*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_OPEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cmtp_application* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cmtp_application *cmtp_application_add(struct cmtp_session *session, __u16 appl)
{
	struct cmtp_application *app = kzalloc(sizeof(*app), GFP_KERNEL);

	BT_DBG("session %p application %p appl %d", session, app, appl);

	if (!app)
		return NULL;

	app->state = BT_OPEN;
	app->appl = appl;

	list_add_tail(&app->list, &session->applications);

	return app;
}