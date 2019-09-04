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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_TLV_ERROR_STRING ; 
 int /*<<< orphan*/  TLV_SPACE (int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tipc_add_tlv (struct sk_buff*,int /*<<< orphan*/ ,char*,int) ; 
 struct sk_buff* tipc_tlv_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *tipc_get_err_tlv(char *str)
{
	int str_len = strlen(str) + 1;
	struct sk_buff *buf;

	buf = tipc_tlv_alloc(TLV_SPACE(str_len));
	if (buf)
		tipc_add_tlv(buf, TIPC_TLV_ERROR_STRING, str, str_len);

	return buf;
}