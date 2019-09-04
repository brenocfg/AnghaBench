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
struct garp_application {int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  stp_proto_unregister (int /*<<< orphan*/ *) ; 

void garp_unregister_application(struct garp_application *appl)
{
	stp_proto_unregister(&appl->proto);
}