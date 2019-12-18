#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_8__ {char* data; TYPE_2__* root; } ;
struct TYPE_6__ {char* (* system ) (int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  io; } ;
struct TYPE_7__ {TYPE_1__ iob; } ;
typedef  TYPE_2__ RFSRoot ;
typedef  TYPE_3__ RFSFile ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (char*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 char* r_fs_file_copy_abs_path (TYPE_3__*) ; 
 int r_hex_str2bin (char*,char*) ; 
 char* r_str_newf (char*,char*) ; 
 int strlen (char*) ; 
 char* stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool fs_io_read(RFSFile *file, ut64 addr, int len) {
	RFSRoot *root = file->root;
	char *abs_path = r_fs_file_copy_abs_path (file);
	if (!abs_path) {
		return false;
	}
	char *cmd = r_str_newf ("mg %s", abs_path);
	R_FREE (abs_path);
	if (!cmd) {
		return false;
	}
	char *res = root->iob.system (root->iob.io, cmd);
	R_FREE (cmd);
	if (res) {
		int encoded_size = strlen (res);
		if (encoded_size != len * 2) {
			eprintf ("Unexpected size (%d vs %d)\n", encoded_size, len*2);
			R_FREE (res);
			return false;
		}
		file->data = (ut8 *) calloc (1, len);
		if (!file->data) {
			R_FREE (res);
			return false;
		}
		int ret = r_hex_str2bin (res, file->data);
		if (ret != len) {
			eprintf ("Inconsistent read\n");
			R_FREE (file->data);
		}
		R_FREE (res);
	}
	return false;
}