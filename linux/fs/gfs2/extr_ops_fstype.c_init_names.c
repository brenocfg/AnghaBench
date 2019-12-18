#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* sb_lockproto; char* sb_locktable; } ;
struct TYPE_4__ {char* ar_lockproto; char* ar_locktable; } ;
struct gfs2_sbd {int sd_fsb2bb_shift; char* sd_proto_name; char* sd_table_name; TYPE_3__* sd_vfs; TYPE_2__ sd_sb; TYPE_1__ sd_args; } ;
struct TYPE_6__ {char* s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_FSNAME_LEN ; 
 int GFS2_SB_ADDR ; 
 int gfs2_read_super (struct gfs2_sbd*,int,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_names(struct gfs2_sbd *sdp, int silent)
{
	char *proto, *table;
	int error = 0;

	proto = sdp->sd_args.ar_lockproto;
	table = sdp->sd_args.ar_locktable;

	/*  Try to autodetect  */

	if (!proto[0] || !table[0]) {
		error = gfs2_read_super(sdp, GFS2_SB_ADDR >> sdp->sd_fsb2bb_shift, silent);
		if (error)
			return error;

		if (!proto[0])
			proto = sdp->sd_sb.sb_lockproto;
		if (!table[0])
			table = sdp->sd_sb.sb_locktable;
	}

	if (!table[0])
		table = sdp->sd_vfs->s_id;

	strlcpy(sdp->sd_proto_name, proto, GFS2_FSNAME_LEN);
	strlcpy(sdp->sd_table_name, table, GFS2_FSNAME_LEN);

	table = sdp->sd_table_name;
	while ((table = strchr(table, '/')))
		*table = '_';

	return error;
}