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
struct TYPE_3__ {int len; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union ism_qi {int /*<<< orphan*/  response; TYPE_2__ request; } ;
struct ism_dev {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ISM_QUERY_INFO ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debug_text_event (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ ism_cmd (struct ism_dev*,union ism_qi*) ; 
 int /*<<< orphan*/  ism_debug_info ; 
 int /*<<< orphan*/  memset (union ism_qi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int query_info(struct ism_dev *ism)
{
	union ism_qi cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.request.hdr.cmd = ISM_QUERY_INFO;
	cmd.request.hdr.len = sizeof(cmd.request);

	if (ism_cmd(ism, &cmd))
		goto out;

	debug_text_event(ism_debug_info, 3, "query info");
	debug_event(ism_debug_info, 3, &cmd.response, sizeof(cmd.response));
out:
	return 0;
}