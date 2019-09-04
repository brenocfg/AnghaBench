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
struct hda_conn_list {int /*<<< orphan*/  list; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int add_conn_list (struct hda_codec*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kfree (struct hda_conn_list*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct hda_conn_list* lookup_conn_list (struct hda_codec*,int /*<<< orphan*/ ) ; 

int snd_hda_override_conn_list(struct hda_codec *codec, hda_nid_t nid, int len,
			       const hda_nid_t *list)
{
	struct hda_conn_list *p;

	p = lookup_conn_list(codec, nid);
	if (p) {
		list_del(&p->list);
		kfree(p);
	}

	return add_conn_list(codec, nid, len, list);
}