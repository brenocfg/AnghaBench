#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  int ut32 ;
typedef  int /*<<< orphan*/  ut16 ;
struct TYPE_19__ {int /*<<< orphan*/  tag; } ;
struct TYPE_18__ {int /*<<< orphan*/  loadaddr; } ;
struct TYPE_17__ {int /*<<< orphan*/  io; TYPE_1__* file; } ;
struct TYPE_16__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RBinJavaObj ;
typedef  TYPE_4__ RBinJavaCPTypeObj ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * r_bin_java_cp_get_bytes (int /*<<< orphan*/ ,int*,int /*<<< orphan*/  const*,scalar_t__ const) ; 
 int r_bin_java_cp_get_size (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* r_bin_java_get_item_from_bin_cp_list (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int r_cmd_java_reload_bin_from_buf (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int r_core_extend_at (TYPE_2__*,scalar_t__,int) ; 
 scalar_t__ r_core_seek (TYPE_2__*,scalar_t__,int) ; 
 scalar_t__ r_core_shift_block (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ r_core_write_at (TYPE_2__*,scalar_t__,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ r_io_read_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ r_io_resize (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ r_io_size (int /*<<< orphan*/ ) ; 
 int r_io_use_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_cmd_java_get_cp_bytes_and_write (RCore *core, RBinJavaObj *obj, ut16 idx, ut64 addr, const ut8 * buf, const ut64 len) {
	int res = false;
	RBinJavaCPTypeObj *cp_obj = r_bin_java_get_item_from_bin_cp_list (obj, idx);
	ut64 c_file_sz = r_io_size (core->io);
	ut32 n_sz = 0, c_sz = obj ? r_bin_java_cp_get_size (obj, idx): -1;
	ut8 * bytes = NULL;

	if (c_sz == -1) {
		return res;
	}

	bytes = r_bin_java_cp_get_bytes (cp_obj->tag, &n_sz, buf, len);

	if (n_sz < c_sz) {
		res = r_core_shift_block (core, addr+c_sz, 0, (int)n_sz - (int)c_sz) &&
		r_io_resize(core->io, c_file_sz + (int) n_sz - (int) c_sz);
	} else if (n_sz > c_sz) {
		res = r_core_extend_at(core, addr,  (int)n_sz - (int)c_sz);
	} else {
		eprintf ("[X] r_cmd_java_get_cp_bytes_and_write: Failed to resize the file correctly aborting.\n");
		return res;
	}

	if (n_sz > 0 && bytes) {
		res = r_core_write_at(core, addr, (const ut8 *)bytes, n_sz) && r_core_seek (core, addr, 1);
	}

	if (res == false) {
		eprintf ("[X] r_cmd_java_get_cp_bytes_and_write: Failed to write the bytes to the file correctly aborting.\n");
		return res;
	}

	R_FREE (bytes);

	if (res == true) {
		ut64 n_file_sz = 0;
		ut8 * bin_buffer = NULL;
		res = r_io_use_fd (core->io, core->file->fd);
		n_file_sz = r_io_size (core->io);
		bin_buffer = n_file_sz > 0 ? malloc (n_file_sz) : NULL;
		if (bin_buffer) {
			memset (bin_buffer, 0, n_file_sz);
			res = n_file_sz == r_io_read_at (core->io, obj->loadaddr,
				bin_buffer, n_file_sz) ? true : false;
			if (res == true) {
				res = r_cmd_java_reload_bin_from_buf (
					core, obj, bin_buffer, n_file_sz);
			} else {
				eprintf ("[X] r_cmd_java_get_cp_bytes_and_write: Failed to read the file in aborted, bin reload.\n");
			}
			free (bin_buffer);
		}
	}
	return res;
}