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
struct TYPE_4__ {scalar_t__ value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  PQExpBuffer ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_NO_OID ; 
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  gss_display_status (scalar_t__*,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_1__*) ; 

__attribute__((used)) static void
pg_GSS_error_int(PQExpBuffer str, const char *mprefix,
				 OM_uint32 stat, int type)
{
	OM_uint32	lmin_s;
	gss_buffer_desc lmsg;
	OM_uint32	msg_ctx = 0;

	do
	{
		gss_display_status(&lmin_s, stat, type,
						   GSS_C_NO_OID, &msg_ctx, &lmsg);
		appendPQExpBuffer(str, "%s: %s\n", mprefix, (char *) lmsg.value);
		gss_release_buffer(&lmin_s, &lmsg);
	} while (msg_ctx);
}