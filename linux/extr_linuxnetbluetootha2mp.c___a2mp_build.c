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
typedef  void* u8 ;
typedef  int u16 ;
struct a2mp_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  len; void* ident; void* code; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct a2mp_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static struct a2mp_cmd *__a2mp_build(u8 code, u8 ident, u16 len, void *data)
{
	struct a2mp_cmd *cmd;
	int plen;

	plen = sizeof(*cmd) + len;
	cmd = kzalloc(plen, GFP_KERNEL);
	if (!cmd)
		return NULL;

	cmd->code = code;
	cmd->ident = ident;
	cmd->len = cpu_to_le16(len);

	memcpy(cmd->data, data, len);

	return cmd;
}