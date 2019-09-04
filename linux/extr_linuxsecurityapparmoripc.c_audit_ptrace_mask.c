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
#define  AA_MAY_BE_READ 131 
#define  AA_MAY_BE_TRACED 130 
#define  MAY_READ 129 
#define  MAY_WRITE 128 
 int /*<<< orphan*/  audit_log_string (struct audit_buffer*,char*) ; 

__attribute__((used)) static void audit_ptrace_mask(struct audit_buffer *ab, u32 mask)
{
	switch (mask) {
	case MAY_READ:
		audit_log_string(ab, "read");
		break;
	case MAY_WRITE:
		audit_log_string(ab, "trace");
		break;
	case AA_MAY_BE_READ:
		audit_log_string(ab, "readby");
		break;
	case AA_MAY_BE_TRACED:
		audit_log_string(ab, "tracedby");
		break;
	}
}