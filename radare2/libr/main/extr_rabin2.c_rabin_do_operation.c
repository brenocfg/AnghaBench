#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  xtr_data; int /*<<< orphan*/ * buf; } ;
struct TYPE_12__ {char* (* signature ) (TYPE_3__*,int) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  loaded; } ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  TYPE_1__ RBinXtrData ;
typedef  TYPE_2__ RBinPlugin ;
typedef  TYPE_3__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  R_MODE_JSON ; 
 int /*<<< orphan*/  UT64_MAX ; 
 int /*<<< orphan*/  __dumpSections (char*) ; 
 int /*<<< orphan*/  bin ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ file ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ output ; 
 TYPE_3__* r_bin_cur (int /*<<< orphan*/ ) ; 
 TYPE_2__* r_bin_file_cur_plugin (TYPE_3__*) ; 
 int /*<<< orphan*/  r_bin_file_object_new_from_xtr_data (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  r_bin_get_laddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_bin_wr_addlib (int /*<<< orphan*/ ,char*) ; 
 int r_bin_wr_entry (int /*<<< orphan*/ ,scalar_t__) ; 
 int r_bin_wr_output (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  r_bin_wr_rpath_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_bin_wr_scn_perms (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  r_bin_wr_scn_resize (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_buf_new_with_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int /*<<< orphan*/  r_cons_println (char*) ; 
 TYPE_1__* r_list_get_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r_num_math (int /*<<< orphan*/ *,char*) ; 
 int r_str_rwx (char*) ; 
 int /*<<< orphan*/  rabin_dump_symbols (scalar_t__) ; 
 int /*<<< orphan*/  rad ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 char* stub1 (TYPE_3__*,int) ; 

__attribute__((used)) static int rabin_do_operation(const char *op) {
	char *arg = NULL, *ptr = NULL, *ptr2 = NULL;
	bool rc = true;

	/* Implement alloca with fixed-size buffer? */
	if (!(arg = strdup (op))) {
		return false;
	}
	if ((ptr = strchr (arg, '/'))) {
		*ptr++ = 0;
		if ((ptr2 = strchr (ptr, '/'))) {
			ptr2[0] = '\0';
			ptr2++;
		}
	}
	if (!output) {
		output = file;
	}
	RBinFile *bf = r_bin_cur (bin);
	if (bf) {
		RBuffer *nb = r_buf_new_with_buf (bf->buf);
		r_buf_free (bf->buf);
		bf->buf = nb;
	}

	switch (arg[0]) {
	case 'e':
		rc = r_bin_wr_entry (bin, r_num_math (NULL, ptr));
		if (rc) {
			rc = r_bin_wr_output (bin, output);
		}
		break;
	case 'd':
		if (!ptr) {
			goto _rabin_do_operation_error;
		}
		switch (*ptr) {
		case 's':
			if (ptr2) {
				if (!rabin_dump_symbols (r_num_math (NULL, ptr2))) {
					goto error;
				}
			} else if (!rabin_dump_symbols (0)) {
				goto error;
			}
			break;
		case 'S':
			if (!ptr2) {
				goto _rabin_do_operation_error;
			}
			if (!__dumpSections (ptr2)) {
				goto error;
			}
			break;
		default:
			goto _rabin_do_operation_error;
		}
		break;
	case 'a':
		if (!ptr) {
			goto _rabin_do_operation_error;
		}
		switch (*ptr) {
		case 'l':
			if (!ptr2 || !r_bin_wr_addlib (bin, ptr2)) {
				goto error;
			}
			rc = r_bin_wr_output (bin, output);
			break;
		default:
			goto _rabin_do_operation_error;
		}
		break;
	case 'R':
		r_bin_wr_rpath_del (bin);
		rc = r_bin_wr_output (bin, output);
		break;
	case 'C':
		{
		RBinFile *cur = r_bin_cur (bin);
		RBinPlugin *plg = r_bin_file_cur_plugin (cur);
		if (!plg && cur) {
			// are we in xtr?
			if (cur->xtr_data) {
				// load the first one
				RBinXtrData *xtr_data = r_list_get_n (cur->xtr_data, 0);
				if (xtr_data && !xtr_data->loaded && !r_bin_file_object_new_from_xtr_data (bin, cur,
					UT64_MAX, r_bin_get_laddr (bin), xtr_data)) {
					break;
				}
			}
			plg = r_bin_file_cur_plugin (cur);
			if (!plg) {
				break;
			}
		}
		if (plg && plg->signature) {
			char *sign = plg->signature (cur, rad == R_MODE_JSON);
			if (sign) {
				r_cons_println (sign);
				r_cons_flush ();
				free (sign);
			}
		}
		}
		break;
	case 'r':
		r_bin_wr_scn_resize (bin, ptr, r_num_math (NULL, ptr2));
		rc = r_bin_wr_output (bin, output);
		break;
	case 'p':
		{
			int perms = (int)r_num_math (NULL, ptr2);
			if (!perms) {
				perms = r_str_rwx (ptr2);
			}
			r_bin_wr_scn_perms (bin, ptr, perms);
			rc = r_bin_wr_output (bin, output);
		}
		break;
	default:
	_rabin_do_operation_error:
		eprintf ("Unknown operation. use -O help\n");
		goto error;
	}
	if (!rc) {
		eprintf ("Cannot dump :(\n");
	}
	free (arg);
	return true;
error:
	free (arg);
	return false;
}