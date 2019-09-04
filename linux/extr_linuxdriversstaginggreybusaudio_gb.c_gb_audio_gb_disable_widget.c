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
struct gb_connection {int dummy; } ;
struct gb_audio_disable_widget_request {int /*<<< orphan*/  widget_id; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  GB_AUDIO_TYPE_DISABLE_WIDGET ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,struct gb_audio_disable_widget_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int gb_audio_gb_disable_widget(struct gb_connection *connection,
			       u8 widget_id)
{
	struct gb_audio_disable_widget_request req;

	req.widget_id = widget_id;

	return gb_operation_sync(connection, GB_AUDIO_TYPE_DISABLE_WIDGET,
				 &req, sizeof(req), NULL, 0);
}