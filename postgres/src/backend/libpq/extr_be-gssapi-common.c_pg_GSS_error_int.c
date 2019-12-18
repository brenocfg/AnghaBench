#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_NO_OID ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*) ; 
 int /*<<< orphan*/  gss_display_status (scalar_t__*,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
pg_GSS_error_int(char *s, size_t len, OM_uint32 stat, int type)
{
	gss_buffer_desc gmsg;
	size_t		i = 0;
	OM_uint32	lmin_s,
				msg_ctx = 0;

	gmsg.value = NULL;
	gmsg.length = 0;

	do
	{
		gss_display_status(&lmin_s, stat, type,
						   GSS_C_NO_OID, &msg_ctx, &gmsg);
		strlcpy(s + i, gmsg.value, len - i);
		i += gmsg.length;
		gss_release_buffer(&lmin_s, &gmsg);
	}
	while (msg_ctx && i < len);

	if (msg_ctx || i == len)
		ereport(WARNING,
				(errmsg_internal("incomplete GSS error report")));
}