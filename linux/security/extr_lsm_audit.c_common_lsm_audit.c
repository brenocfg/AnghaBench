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
typedef  void common_audit_data ;
typedef  struct audit_buffer audit_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_AVC ; 
 int GFP_ATOMIC ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_common_audit_data (struct audit_buffer*,void*) ; 

void common_lsm_audit(struct common_audit_data *a,
	void (*pre_audit)(struct audit_buffer *, void *),
	void (*post_audit)(struct audit_buffer *, void *))
{
	struct audit_buffer *ab;

	if (a == NULL)
		return;
	/* we use GFP_ATOMIC so we won't sleep */
	ab = audit_log_start(audit_context(), GFP_ATOMIC | __GFP_NOWARN,
			     AUDIT_AVC);

	if (ab == NULL)
		return;

	if (pre_audit)
		pre_audit(ab, a);

	dump_common_audit_data(ab, a);

	if (post_audit)
		post_audit(ab, a);

	audit_log_end(ab);
}