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
struct tipc_nl_compat_msg {int /*<<< orphan*/  rep; int /*<<< orphan*/  req; } ;
struct tipc_name_table_query {int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TLV_DATA (int /*<<< orphan*/ ) ; 
 int TLV_GET_DATA_LEN (int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_tlv_sprintf (int /*<<< orphan*/ ,char const* const) ; 

__attribute__((used)) static int tipc_nl_compat_name_table_dump_header(struct tipc_nl_compat_msg *msg)
{
	int i;
	u32 depth;
	struct tipc_name_table_query *ntq;
	static const char * const header[] = {
		"Type       ",
		"Lower      Upper      ",
		"Port Identity              ",
		"Publication Scope"
	};

	ntq = (struct tipc_name_table_query *)TLV_DATA(msg->req);
	if (TLV_GET_DATA_LEN(msg->req) < sizeof(struct tipc_name_table_query))
		return -EINVAL;

	depth = ntohl(ntq->depth);

	if (depth > 4)
		depth = 4;
	for (i = 0; i < depth; i++)
		tipc_tlv_sprintf(msg->rep, header[i]);
	tipc_tlv_sprintf(msg->rep, "\n");

	return 0;
}