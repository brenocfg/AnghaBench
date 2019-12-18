#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int ut64 ;
struct count_pz_t {int addr; int* ret; int size; int /*<<< orphan*/  flagspace; } ;
struct TYPE_12__ {int /*<<< orphan*/  bbs; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  anal; } ;
struct TYPE_10__ {TYPE_1__* block; } ;
struct TYPE_9__ {int functions; int in_functions; int comments; int symbols; int flags; int strings; int blocks; } ;
typedef  TYPE_2__ RCoreAnalStats ;
typedef  TYPE_3__ RCore ;
typedef  TYPE_4__ RAnalFunction ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PRINTABLE (int) ; 
 int /*<<< orphan*/  R_FLAGS_FS_STRINGS ; 
 int /*<<< orphan*/  count_pzf ; 
 int /*<<< orphan*/  count_pzs ; 
 TYPE_4__* r_anal_get_fcn_in (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* r_core_anal_get_stats (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  r_core_anal_stats_free (TYPE_2__*) ; 
 int /*<<< orphan*/  r_flag_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct count_pz_t*) ; 
 int /*<<< orphan*/  r_flag_space_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int r_hash_entropy_fraction (int*,int) ; 
 int r_list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int printzoomcallback(void *user, int mode, ut64 addr, ut8 *bufz, ut64 size) {
	RCore *core = (RCore *) user;
	int j, ret = 0;
	struct count_pz_t u;

	switch (mode) {
	case 'a':
		{
		RAnalFunction *fcn = r_anal_get_fcn_in (core->anal, addr, 0);
		int value = 0;
		if (fcn) {
			value = r_list_length (fcn->bbs);
		}
		return value;
		}
		break;
	case 'A':
		{
		RCoreAnalStats *as = r_core_anal_get_stats (core, addr, addr + size * 2, size);
		int i;
		int value = 0;
		for (i = 0; i < 1; i++) {
			value += as->block[i].functions;
			value += as->block[i].in_functions;
			value += as->block[i].comments;
			value += as->block[i].symbols;
			value += as->block[i].flags;
			value += as->block[i].strings;
			value += as->block[i].blocks;
			value *= 20;
		}
		r_core_anal_stats_free (as);
		return value;
		}
		break;
	case '0': // "pz0"
		for (j = 0; j < size; j++) {
			if (bufz[j] == 0) {
				ret++;
			}
		}
		break;
	case 'e': // "pze"
		ret = (ut8) (r_hash_entropy_fraction (bufz, size) * 255);
		break;
	case 'f': // "pzf"
		u.addr = addr;
		u.ret = &ret;
		r_flag_foreach (core->flags, count_pzf, &u);
		break;
	case 'F': // "pzF"
		for (j = 0; j < size; j++) {
			if (bufz[j] == 0xff) {
				ret++;
			}
		}
		break;
	case 'p': // "pzp"
		for (j = 0; j < size; j++) {
			if (IS_PRINTABLE (bufz[j])) {
				ret++;
			}
		}
		break;
	case 's': // "pzs"
		u.flagspace = r_flag_space_get (core->flags, R_FLAGS_FS_STRINGS);
		u.addr = addr;
		u.size = size;
		u.ret = &ret;
		r_flag_foreach (core->flags, count_pzs, &u);
		break;
	case 'h': // "pzh" head
	default:
		ret = *bufz;
	}
	return ret;
}