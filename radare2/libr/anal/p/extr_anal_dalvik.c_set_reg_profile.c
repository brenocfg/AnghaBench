#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 int r_reg_set_profile_string (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int set_reg_profile(RAnal *anal) {
	const char *p =
	"=PC	ip\n"
	"=SP	sp\n"
	"=BP	bp\n"
	"=A0	v0\n"
	"=A1	v1\n"
	"=A2	v2\n"
	"=A3	v3\n"
	"=SN	v0\n"
	"gpr	v0	.32	0	0\n"
	"gpr	v1	.32	4	0\n"
	"gpr	v2	.32	8	0\n"
	"gpr	v3	.32	12	0\n"
	"gpr	v4	.32	16	0\n"
	"gpr	v5	.32	20	0\n"
	"gpr	v6	.32	24	0\n"
	"gpr	v7	.32	28	0\n"
	"gpr	v8	.32	32	0\n"
	"gpr	v9	.32	36	0\n"
	"gpr	v10	.32	40	0\n"
	"gpr	v11	.32	44	0\n"
	"gpr	v12	.32	48	0\n"
	"gpr	v13	.32	52	0\n"
	"gpr	v14	.32	56	0\n"
	"gpr	v15	.32	60	0\n"
	"gpr	v16	.32	40	0\n"
	"gpr	v17	.32	44	0\n"
	"gpr	v18	.32	48	0\n"
	"gpr	v19	.32	52	0\n"
	"gpr	v20	.32	56	0\n"
	"gpr	v21	.32	60	0\n"
	"gpr	v22	.32	64	0\n"
	"gpr	v23	.32	68	0\n"
	"gpr	v24	.32	72	0\n"
	"gpr	v25	.32	76	0\n"
	"gpr	v26	.32	80	0\n"
	"gpr	v27	.32	84	0\n"
	"gpr	v28	.32	88	0\n"
	"gpr	v29	.32	92	0\n"
	"gpr	v30	.32	96	0\n"
	"gpr	v31	.32	100	0\n"
	"gpr	v32	.32	104	0\n"
	"gpr	v33	.32	108	0\n"
	"gpr	v34	.32	112	0\n"
	"gpr	ip	.32	116	0\n"
	"gpr	sp	.32	120	0\n"
	"gpr	bp	.32	124	0\n"
	;
	return r_reg_set_profile_string (anal->reg, p);
}