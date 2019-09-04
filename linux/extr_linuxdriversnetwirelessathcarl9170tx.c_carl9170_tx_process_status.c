#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int ext; int len; } ;
struct carl9170_rsp {TYPE_1__* _tx_status; TYPE_2__ hdr; } ;
struct ar9170 {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  info; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __carl9170_tx_process_status (struct ar9170*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,void*,int) ; 

void carl9170_tx_process_status(struct ar9170 *ar,
				const struct carl9170_rsp *cmd)
{
	unsigned int i;

	for (i = 0;  i < cmd->hdr.ext; i++) {
		if (WARN_ON(i > ((cmd->hdr.len / 2) + 1))) {
			print_hex_dump_bytes("UU:", DUMP_PREFIX_NONE,
					     (void *) cmd, cmd->hdr.len + 4);
			break;
		}

		__carl9170_tx_process_status(ar, cmd->_tx_status[i].cookie,
					     cmd->_tx_status[i].info);
	}
}