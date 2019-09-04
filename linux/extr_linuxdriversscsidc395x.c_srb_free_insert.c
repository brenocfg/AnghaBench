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
struct ScsiReqBlk {int /*<<< orphan*/  list; } ;
struct AdapterCtlBlk {int /*<<< orphan*/  srb_free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void srb_free_insert(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb)
{
	dprintkdbg(DBG_0, "srb_free_insert: srb=%p\n", srb);
	list_add_tail(&srb->list, &acb->srb_free_list);
}