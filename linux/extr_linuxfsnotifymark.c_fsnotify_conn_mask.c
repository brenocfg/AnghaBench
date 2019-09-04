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
struct fsnotify_mark_connector {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/ * fsnotify_conn_mask_p (struct fsnotify_mark_connector*) ; 
 int /*<<< orphan*/  fsnotify_valid_obj_type (int /*<<< orphan*/ ) ; 

__u32 fsnotify_conn_mask(struct fsnotify_mark_connector *conn)
{
	if (WARN_ON(!fsnotify_valid_obj_type(conn->type)))
		return 0;

	return *fsnotify_conn_mask_p(conn);
}