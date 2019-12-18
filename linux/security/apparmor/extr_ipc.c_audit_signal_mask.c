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
typedef  int u32 ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int MAY_READ ; 
 int MAY_WRITE ; 
 int /*<<< orphan*/  audit_log_string (struct audit_buffer*,char*) ; 

__attribute__((used)) static void audit_signal_mask(struct audit_buffer *ab, u32 mask)
{
	if (mask & MAY_READ)
		audit_log_string(ab, "receive");
	if (mask & MAY_WRITE)
		audit_log_string(ab, "send");
}