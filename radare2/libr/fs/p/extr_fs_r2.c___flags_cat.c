#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_11__ {void* size; int /*<<< orphan*/  p; int /*<<< orphan*/ * data; int /*<<< orphan*/ * ptr; } ;
struct TYPE_9__ {char* (* cmdstrf ) (int /*<<< orphan*/ ,char*,char const*) ;int /*<<< orphan*/  core; } ;
struct TYPE_10__ {int /*<<< orphan*/  p; TYPE_1__ cob; } ;
typedef  TYPE_2__ RFSRoot ;
typedef  TYPE_3__ RFSFile ;

/* Variables and functions */
 TYPE_3__* r_fs_file_new (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int /*<<< orphan*/ *) ; 
 char* r_str_rchr (char const*,int /*<<< orphan*/ *,char) ; 
 void* strlen (char*) ; 
 char* stub1 (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static RFSFile *__flags_cat(RFSRoot *root, RFSFile *file, const char *path) {
	r_return_val_if_fail (root && path, NULL);
	const char *last = r_str_rchr (path, NULL, '/');
	if (last) {
		last++;
	} else {
		last = path;
	}
	char *res = root->cob.cmdstrf (root->cob.core, "?v %s", last);
	if (file) {
		file->ptr = NULL;
		file->data = (ut8*)res;
		file->p = root->p;
		file->size = strlen (res);
	} else {
		file = r_fs_file_new (root, path);
		file->ptr = NULL;
		file->data = (ut8*)res;
		file->p = root->p;
		file->size = strlen (res);
	}
	return file;
}