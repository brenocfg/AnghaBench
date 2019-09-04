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
struct netlbl_audit {int dummy; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 struct audit_buffer* netlbl_audit_start_common (int,struct netlbl_audit*) ; 

struct audit_buffer *netlbl_audit_start(int type,
					struct netlbl_audit *audit_info)
{
	return netlbl_audit_start_common(type, audit_info);
}