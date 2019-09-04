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
typedef  int /*<<< orphan*/  u32 ;
struct hgsmi_host_flags {int dummy; } ;
struct hgsmi_buffer_location {int buf_len; int /*<<< orphan*/  buf_location; } ;
struct gen_pool {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HGSMI_CC_HOST_FLAGS_LOCATION ; 
 int /*<<< orphan*/  HGSMI_CH_HGSMI ; 
 struct hgsmi_buffer_location* hgsmi_buffer_alloc (struct gen_pool*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hgsmi_buffer_free (struct gen_pool*,struct hgsmi_buffer_location*) ; 
 int /*<<< orphan*/  hgsmi_buffer_submit (struct gen_pool*,struct hgsmi_buffer_location*) ; 

int hgsmi_report_flags_location(struct gen_pool *ctx, u32 location)
{
	struct hgsmi_buffer_location *p;

	p = hgsmi_buffer_alloc(ctx, sizeof(*p), HGSMI_CH_HGSMI,
			       HGSMI_CC_HOST_FLAGS_LOCATION);
	if (!p)
		return -ENOMEM;

	p->buf_location = location;
	p->buf_len = sizeof(struct hgsmi_host_flags);

	hgsmi_buffer_submit(ctx, p);
	hgsmi_buffer_free(ctx, p);

	return 0;
}