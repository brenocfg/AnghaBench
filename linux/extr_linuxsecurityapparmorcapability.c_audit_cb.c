#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t cap; } ;
struct common_audit_data {TYPE_1__ u; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*) ; 
 int /*<<< orphan*/  audit_log_untrustedstring (struct audit_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * capability_names ; 

__attribute__((used)) static void audit_cb(struct audit_buffer *ab, void *va)
{
	struct common_audit_data *sa = va;

	audit_log_format(ab, " capname=");
	audit_log_untrustedstring(ab, capability_names[sa->u.cap]);
}