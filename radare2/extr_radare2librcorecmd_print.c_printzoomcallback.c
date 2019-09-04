#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int ut64 ;
struct count_pz_t {int addr; int* ret; int size; int /*<<< orphan*/  flagspace; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PRINTABLE (int) ; 
 int /*<<< orphan*/  R_FLAGS_FS_STRINGS ; 
 int /*<<< orphan*/  count_pzf ; 
 int /*<<< orphan*/  count_pzs ; 
 int /*<<< orphan*/  r_flag_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct count_pz_t*) ; 
 int /*<<< orphan*/  r_flag_space_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int r_hash_entropy_fraction (int*,int) ; 

__attribute__((used)) static int printzoomcallback(void *user, int mode, ut64 addr, ut8 *bufz, ut64 size) {
	RCore *core = (RCore *) user;
	int j, ret = 0;
	struct count_pz_t u;

	switch (mode) {
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