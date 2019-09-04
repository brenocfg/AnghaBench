#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct r_bin_java_obj_t {int /*<<< orphan*/  file; int /*<<< orphan*/  AllJavaBinObjs; int /*<<< orphan*/  kv; } ;
struct TYPE_6__ {scalar_t__ file; TYPE_1__* o; int /*<<< orphan*/  sdb; int /*<<< orphan*/  buf; } ;
struct TYPE_5__ {struct r_bin_java_obj_t* bin_obj; int /*<<< orphan*/  kv; int /*<<< orphan*/  loadaddr; } ;
typedef  TYPE_2__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  DB ; 
 int /*<<< orphan*/  add_bin_obj_to_sdb (struct r_bin_java_obj_t*) ; 
 int /*<<< orphan*/  load_bytes (TYPE_2__*,void**,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_buf_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (scalar_t__) ; 

__attribute__((used)) static bool load(RBinFile *bf) {
	if (!bf || !bf->o) {
		return false;
	}

	int result = false;
	ut64 sz;
	const ut8 *bytes = r_buf_buffer (bf->buf, &sz);
	struct r_bin_java_obj_t *bin_obj = NULL;

	load_bytes (bf, (void **)&bin_obj, bytes, sz, bf->o->loadaddr, bf->sdb);

	if (bin_obj) {
		if (!bf->o->kv) {
			bf->o->kv = bin_obj->kv;
		}
		bf->o->bin_obj = bin_obj;
		bin_obj->AllJavaBinObjs = DB;
		// XXX - /\ this is a hack, but (one way but) necessary to get access to
		// the object addrs from anal. If only global variables are used,
		// they get "lost" somehow after they are initialized and go out of
		// scope.
		//
		// There are several points of indirection, but here is the gist:
		// 1) RAnal->(through RBinBind) RBin->RBinJavaObj->DB
		//
		// The purpose is to ensure that information about a give class file
		// can be grabbed at any time from RAnal.  This was tried with global
		// variables, but failed when attempting to access the DB
		// in the class.c scope.  Once DB  was moved here, it is initialized
		// once here and assigned to each of the other RBinJavaObjs.
		//
		// Now, the RAnal component of radare can get to each of the
		// RBinJavaObjs for analysing functions and dependencies using an Sdb.
		add_bin_obj_to_sdb (bin_obj);
		if (bf->file) {
			bin_obj->file = strdup (bf->file);
		}
		result = true;
	}
	return result;
}