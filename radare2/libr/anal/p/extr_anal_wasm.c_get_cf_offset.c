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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_4__ {char* (* cmdstrf ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  core; } ;
struct TYPE_5__ {TYPE_1__ coreb; } ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  UT64_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_pop () ; 
 int /*<<< orphan*/  r_cons_push () ; 
 int /*<<< orphan*/  r_num_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  read_u32_leb128 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 char* stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ut64 get_cf_offset(RAnal *anal, const ut8 *data, int len) {
	ut32 fcn_id;

	if (!read_u32_leb128 (&data[1], &data[len - 1], &fcn_id)) {
		return UT64_MAX;
	}
	r_cons_push ();
	// 0xfff.. are bad addresses for wasm
	// cgvwzq: 0xfff... can be external imported JS funcs
	char *s = anal->coreb.cmdstrf (anal->coreb.core, "is~FUNC[2:%u]", fcn_id);
	r_cons_pop ();
	if (s) {
		ut64 n = r_num_get (NULL, s);
		free (s);
		return n;
	}
	return UT64_MAX;
}