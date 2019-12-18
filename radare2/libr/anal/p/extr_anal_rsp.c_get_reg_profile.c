#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 char* strdup (char const*) ; 

__attribute__((used)) static char *get_reg_profile(RAnal *anal) {
	static const char *p =
		"=PC    pc\n"
		"=SP    sp\n"
		"=A0    a0\n"
		"=A1    a1\n"
		"=A2    a2\n"
		"=A3    a3\n"
		"=R0    v0\n"
		"=R1    v1\n"
/* GP registers */
		"gpr	zero	.32	0	0\n"
		"gpr	at	.32	4	0\n"
		"gpr	v0	.32	8	0\n"
		"gpr	v1	.32	12	0\n"
		"gpr	a0	.32	16	0\n"
		"gpr	a1	.32	20	0\n"
		"gpr	a2	.32	24	0\n"
		"gpr	a3	.32	28	0\n"
		"gpr	t0	.32	32	0\n"
		"gpr	t1	.32	36	0\n"
		"gpr	t2	.32	40	0\n"
		"gpr	t3	.32	44	0\n"
		"gpr	t4	.32	48	0\n"
		"gpr	t5	.32	52	0\n"
		"gpr	t6	.32	56	0\n"
		"gpr	t7	.32	60	0\n"
		"gpr	s0	.32	64	0\n"
		"gpr	s1	.32	68	0\n"
		"gpr	s2	.32	72	0\n"
		"gpr	s3	.32	76	0\n"
		"gpr	s4	.32	80	0\n"
		"gpr	s5	.32	84	0\n"
		"gpr	s6	.32	88	0\n"
		"gpr	s7	.32	92	0\n"
		"gpr	t8	.32	96	0\n"
		"gpr	t9	.32	100	0\n"
		"gpr	k0	.32	104	0\n"
		"gpr	k1	.32	108	0\n"
		"gpr	gp	.32	112	0\n"
		"gpr	sp	.32	116	0\n"
		"gpr	s8	.32	120	0\n"
		"gpr	ra	.32	124	0\n"
/* PC register */
		"gpr	pc	.32	128	0\n"
/* C0 registers */
		"gpr	$c0	.32	132	0\n"
		"gpr	$c1	.32	136	0\n"
		"gpr	$c2	.32	140	0\n"
		"gpr	$c3	.32	144	0\n"
		"gpr	$c4	.32	148	0\n"
		"gpr	$c5	.32	152	0\n"
		"gpr	$c6	.32	156	0\n"
		"gpr	$c7	.32	160	0\n"
		"gpr	$c8	.32	164	0\n"
		"gpr	$c9	.32	168	0\n"
		"gpr	$c10	.32	172	0\n"
		"gpr	$c11	.32	176	0\n"
		"gpr	$c12	.32	180	0\n"
		"gpr	$c13	.32	184	0\n"
		"gpr	$c14	.32	188	0\n"
		"gpr	$c15	.32	192	0\n"
/* C2 vector registers - (32 x 128 bit) */
		"gpr	$v0	.128	196	0\n"
		"gpr	$v1	.128	212	0\n"
		"gpr	$v2	.128	228	0\n"
		"gpr	$v3	.128	244	0\n"
		"gpr	$v4	.128	260	0\n"
		"gpr	$v5	.128	276	0\n"
		"gpr	$v6	.128	292	0\n"
		"gpr	$v7	.128	308	0\n"
		"gpr	$v8	.128	324	0\n"
		"gpr	$v9	.128	340	0\n"
		"gpr	$v10	.128	356	0\n"
		"gpr	$v11	.128	372	0\n"
		"gpr	$v12	.128	388	0\n"
		"gpr	$v13	.128	404	0\n"
		"gpr	$v14	.128	420	0\n"
		"gpr	$v15	.128	436	0\n"
		"gpr	$v16	.128	452	0\n"
		"gpr	$v17	.128	468	0\n"
		"gpr	$v18	.128	484	0\n"
		"gpr	$v19	.128	500	0\n"
		"gpr	$v20	.128	516	0\n"
		"gpr	$v21	.128	532	0\n"
		"gpr	$v22	.128	548	0\n"
		"gpr	$v23	.128	564	0\n"
		"gpr	$v24	.128	580	0\n"
		"gpr	$v25	.128	596	0\n"
		"gpr	$v26	.128	612	0\n"
		"gpr	$v27	.128	628	0\n"
		"gpr	$v28	.128	644	0\n"
		"gpr	$v29	.128	660	0\n"
		"gpr	$v30	.128	676	0\n"
		"gpr	$v31	.128	692	0\n"
/* C2 control registers - (vco, vcc, vce) */
		"gpr    $vco	.128	708	0\n"
		"gpr    $vcc	.128	724	0\n"
		"gpr    $vce	.128	740	0\n"
	;

	return strdup (p);
}