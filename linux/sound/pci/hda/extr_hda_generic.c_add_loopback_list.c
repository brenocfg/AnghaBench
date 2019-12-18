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
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  amplist; } ;
struct hda_gen_spec {TYPE_2__ loopback_list; TYPE_1__ loopback; } ;
struct hda_amp_list {int idx; int /*<<< orphan*/  dir; int /*<<< orphan*/  nid; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 struct hda_amp_list* snd_array_new (TYPE_2__*) ; 

__attribute__((used)) static int add_loopback_list(struct hda_gen_spec *spec, hda_nid_t mix, int idx)
{
	struct hda_amp_list *list;

	list = snd_array_new(&spec->loopback_list);
	if (!list)
		return -ENOMEM;
	list->nid = mix;
	list->dir = HDA_INPUT;
	list->idx = idx;
	spec->loopback.amplist = spec->loopback_list.list;
	return 0;
}