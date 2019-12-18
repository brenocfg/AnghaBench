#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long long ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_5__ {int perm; int /*<<< orphan*/  uri; int /*<<< orphan*/  fd; TYPE_1__* io; } ;
struct TYPE_4__ {TYPE_2__* desc; } ;
typedef  TYPE_2__ RIODesc ;
typedef  int /*<<< orphan*/  PJ ;

/* Variables and functions */
 int R_PERM_W ; 
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_kN (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pj_kb (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pj_kn (int /*<<< orphan*/ *,char*,long long) ; 
 int /*<<< orphan*/  pj_ks (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pj_o (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_io_desc_size (TYPE_2__*) ; 

__attribute__((used)) static bool desc_list_json_cb(void *user, void *data, ut32 id) {
	PJ *pj = (PJ *)user;
	RIODesc *desc = (RIODesc *)data;
	// TODO: from is always 0? See libr/core/file.c:945
	ut64 from = 0LL;
	pj_o (pj);
	pj_kb (pj, "raised", desc->io && (desc->io->desc == desc));
	pj_kN (pj, "fd", desc->fd);
	pj_ks (pj, "uri", desc->uri);
	pj_kn (pj, "from", from);
	pj_kb (pj, "writable", desc->perm & R_PERM_W);
	pj_kN (pj, "size", r_io_desc_size (desc));
	pj_end (pj);
	return true;
}