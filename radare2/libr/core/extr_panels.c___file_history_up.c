#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* io; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  index; } ;
struct TYPE_10__ {int file_hist_index; TYPE_2__ buffer; TYPE_5__* user; } ;
struct TYPE_8__ {int /*<<< orphan*/  files; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_3__ RLine ;
typedef  TYPE_4__ RIODesc ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 scalar_t__ R_LINE_BUFSIZE ; 
 int /*<<< orphan*/ * r_id_storage_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 TYPE_4__* r_list_get_n (int /*<<< orphan*/ *,int) ; 
 int r_list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int __file_history_up(RLine *line) {
	RCore *core = line->user;
	RList *files = r_id_storage_list (core->io->files);
	int num_files = r_list_length (files);
	if (line->file_hist_index >= num_files || line->file_hist_index < 0) {
		return false;
	}
	line->file_hist_index++;
	RIODesc *desc = r_list_get_n (files, num_files - line->file_hist_index);
	if (desc) {
		strncpy (line->buffer.data, desc->name, R_LINE_BUFSIZE - 1);
		line->buffer.index = line->buffer.length = strlen (line->buffer.data);
	}
	r_list_free (files);
	return true;
}