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
struct hdac_device {int /*<<< orphan*/  dev; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 unsigned int AC_CLIST_LENGTH ; 
 unsigned int AC_CLIST_LONG ; 
 int /*<<< orphan*/  AC_VERB_GET_CONNECT_LIST ; 
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 unsigned int get_num_conns (struct hdac_device*,int) ; 
 int snd_hdac_read (struct hdac_device*,int,int /*<<< orphan*/ ,int,unsigned int*) ; 

int snd_hdac_get_connections(struct hdac_device *codec, hda_nid_t nid,
			     hda_nid_t *conn_list, int max_conns)
{
	unsigned int parm;
	int i, conn_len, conns, err;
	unsigned int shift, num_elems, mask;
	hda_nid_t prev_nid;
	int null_count = 0;

	parm = get_num_conns(codec, nid);
	if (!parm)
		return 0;

	if (parm & AC_CLIST_LONG) {
		/* long form */
		shift = 16;
		num_elems = 2;
	} else {
		/* short form */
		shift = 8;
		num_elems = 4;
	}
	conn_len = parm & AC_CLIST_LENGTH;
	mask = (1 << (shift-1)) - 1;

	if (!conn_len)
		return 0; /* no connection */

	if (conn_len == 1) {
		/* single connection */
		err = snd_hdac_read(codec, nid, AC_VERB_GET_CONNECT_LIST, 0,
				    &parm);
		if (err < 0)
			return err;
		if (conn_list)
			conn_list[0] = parm & mask;
		return 1;
	}

	/* multi connection */
	conns = 0;
	prev_nid = 0;
	for (i = 0; i < conn_len; i++) {
		int range_val;
		hda_nid_t val, n;

		if (i % num_elems == 0) {
			err = snd_hdac_read(codec, nid,
					    AC_VERB_GET_CONNECT_LIST, i,
					    &parm);
			if (err < 0)
				return -EIO;
		}
		range_val = !!(parm & (1 << (shift-1))); /* ranges */
		val = parm & mask;
		if (val == 0 && null_count++) {  /* no second chance */
			dev_dbg(&codec->dev,
				"invalid CONNECT_LIST verb %x[%i]:%x\n",
				nid, i, parm);
			return 0;
		}
		parm >>= shift;
		if (range_val) {
			/* ranges between the previous and this one */
			if (!prev_nid || prev_nid >= val) {
				dev_warn(&codec->dev,
					 "invalid dep_range_val %x:%x\n",
					 prev_nid, val);
				continue;
			}
			for (n = prev_nid + 1; n <= val; n++) {
				if (conn_list) {
					if (conns >= max_conns)
						return -ENOSPC;
					conn_list[conns] = n;
				}
				conns++;
			}
		} else {
			if (conn_list) {
				if (conns >= max_conns)
					return -ENOSPC;
				conn_list[conns] = val;
			}
			conns++;
		}
		prev_nid = val;
	}
	return conns;
}