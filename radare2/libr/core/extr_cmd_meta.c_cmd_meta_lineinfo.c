#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
struct TYPE_12__ {TYPE_1__* cur; } ;
struct TYPE_11__ {scalar_t__ sdb_addrinfo; } ;
struct TYPE_10__ {TYPE_6__* bin; int /*<<< orphan*/  num; scalar_t__ offset; } ;
struct TYPE_9__ {int /*<<< orphan*/  sdb_addrinfo; } ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RBinFile ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 
 int cmd_meta_add_fileline (scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ filter_count ; 
 char filter_format ; 
 scalar_t__ filter_offset ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  print_addrinfo ; 
 int /*<<< orphan*/  print_meta_offset (TYPE_2__*,scalar_t__) ; 
 TYPE_3__* r_bin_cur (TYPE_6__*) ; 
 scalar_t__ r_num_math (int /*<<< orphan*/ ,char const*) ; 
 char* r_str_trim_ro (char const*) ; 
 int /*<<< orphan*/  remove_meta_offset (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/ * sdb_decode (char*,int*) ; 
 int /*<<< orphan*/  sdb_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdb_reset (int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int cmd_meta_lineinfo(RCore *core, const char *input) {
	int ret;
	ut64 offset = UT64_MAX; // use this as error value
	bool remove = false;
	int all = false;
	const char *p = input;
	char *file_line = NULL;
	char *pheap = NULL;

	if (*p == '?') {
		eprintf ("Usage: CL[.-*?] [addr] [file:line]\n");
		eprintf ("or: CL [addr] base64:[string]\n");
		free (pheap);
		return 0;
	}
	if (*p == '-') {
		p++;
		remove = true;
	}
	if (*p == '.') {
		p++;
		offset = core->offset;
	}
	if (*p == ' ') {
		p = r_str_trim_ro (p + 1);
		char *arg = strchr (p, ' ');
		if (!arg) {
			offset = r_num_math (core->num, p);
			p = "";
		}
	} else if (*p == '*') {
		p++;
		all = true;
		filter_format = '*';
	} else {
		filter_format = 0;
	}

	if (all) {
		if (remove) {
			sdb_reset (core->bin->cur->sdb_addrinfo);
		} else {
			sdb_foreach (core->bin->cur->sdb_addrinfo, print_addrinfo, NULL);
		}
		free (pheap);
		return 0;
	}

	p = r_str_trim_ro (p);
	char *myp = strdup (p);
	char *sp = strchr (myp, ' ');
	if (sp) {
		*sp = 0;
		sp++;
		if (offset == UT64_MAX) {
			offset = r_num_math (core->num, myp);
		}

		if (!strncmp (sp, "base64:", 7)) {
			int len = 0;
			ut8 *o = sdb_decode (sp + 7, &len);
			if (!o) {
				eprintf ("Invalid base64\n");
				return 0;
			}
			sp = pheap = (char *)o;
		}
		RBinFile *bf = r_bin_cur (core->bin);
		ret = 0;
		if (bf && bf->sdb_addrinfo) {
			ret = cmd_meta_add_fileline (bf->sdb_addrinfo, sp, offset);
		} else {
			eprintf ("TODO: Support global SdbAddrinfo or dummy rbinfile to handlee this case\n");
		}
		free (file_line);
		free (myp);
		free (pheap);
		return ret;
	}
	free (myp);
	if (remove) {
		remove_meta_offset (core, offset);
	} else {
		// taken from r2 // TODO: we should move this addrinfo sdb logic into RBin.. use HT
		filter_offset = offset;
		filter_count = 0;
		sdb_foreach (core->bin->cur->sdb_addrinfo, print_addrinfo, NULL);
		if (filter_count == 0) {
			print_meta_offset (core, offset);
		}
	}
	free (pheap);
	return 0;
}