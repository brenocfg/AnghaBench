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
	/* As far as I can see, sparc v9 register and instruction set
	   don't depened  on bits of the running application.
	   But: They depend on the bits of the consuming application,
	   that is the bits radare had been compiled with.
	   See sys/procfs_isa.h on a Solaris10 Sparc machine and
	   'man 4 core' for reference.
	 */
	const char *p =
	"=PC	pc\n"
	"=SP	o6\n"
	"=BP	i6\n"
	/* prgregset_t for _LP64 */
	"gpr	g0	.64	0	0\n"
	"gpr	g1	.64	8	0\n"
	"gpr	g2	.64	16	0\n"
	"gpr	g3	.64	24	0\n"
	"gpr	g4	.64	32	0\n"
	"gpr	g5	.64	40	0\n"
	"gpr	g6	.64	48	0\n"
	"gpr	g7	.64	56	0\n"
	"gpr	o0	.64	64	0\n"
	"gpr	o1	.64	72	0\n"
	"gpr	o2	.64	80	0\n"
	"gpr	o3	.64	88	0\n"
	"gpr	o4	.64	96	0\n"
	"gpr	o5	.64	104	0\n"
	"gpr	o6	.64	112	0\n"
	"gpr	o7	.64	120	0\n"
	"gpr	l0	.64	128	0\n"
	"gpr	l1	.64	136	0\n"
	"gpr	l2	.64	144	0\n"
	"gpr	l3	.64	152	0\n"
	"gpr	l4	.64	160	0\n"
	"gpr	l5	.64	168	0\n"
	"gpr	l6	.64	176	0\n"
	"gpr	l7	.64	184	0\n"
	"gpr	i0	.64	192	0\n"
	"gpr	i1	.64	200	0\n"
	"gpr	i2	.64	208	0\n"
	"gpr	i3	.64	216	0\n"
	"gpr	i4	.64	224	0\n"
	"gpr	i5	.64	232	0\n"
	"gpr	i6	.64	240	0\n"
	"gpr	i7	.64	248	0\n"
	"gpr	ccr	.64	256	0\n"
	"gpr	pc	.64	264	0\n"
	"gpr	ncp	.64	272	0\n"
	"gpr	y	.64	280	0\n"
	"gpr	asi	.64	288	0\n"
	"gpr	fprs	.64	296	0\n"
	/* beginning of prfpregset_t for __sparcv9 */
	"fpu	sf0	.32	304	0\n"
	"fpu	sf1	.32	308	0\n"
	"fpu	sf2	.32	312	0\n"
	"fpu	sf3	.32	316	0\n"
	"fpu	sf4	.32	320	0\n"
	"fpu	sf5	.32	324	0\n"
	"fpu	sf6	.32	328	0\n"
	"fpu	sf7	.32	332	0\n"
	"fpu	sf8	.32	336	0\n"
	"fpu	sf9	.32	340	0\n"
	"fpu	sf10	.32	344	0\n"
	"fpu	sf11	.32	348	0\n"
	"fpu	sf12	.32	352	0\n"
	"fpu	sf13	.32	356	0\n"
	"fpu	sf14	.32	360	0\n"
	"fpu	sf15	.32	364	0\n"
	"fpu	sf16	.32	368	0\n"
	"fpu	sf17	.32	372	0\n"
	"fpu	sf18	.32	376	0\n"
	"fpu	sf19	.32	380	0\n"
	"fpu	sf20	.32	384	0\n"
	"fpu	sf21	.32	388	0\n"
	"fpu	sf22	.32	392	0\n"
	"fpu	sf23	.32	396	0\n"
	"fpu	sf24	.32	400	0\n"
	"fpu	sf25	.32	404	0\n"
	"fpu	sf26	.32	408	0\n"
	"fpu	sf27	.32	412	0\n"
	"fpu	sf28	.32	416	0\n"
	"fpu	sf29	.32	420	0\n"
	"fpu	sf30	.32	424	0\n"
	"fpu	sf31	.32	428	0\n"
	"fpu	df0	.64	304	0\n"	/* sf0 sf1 */
	"fpu	df2	.64	312	0\n"	/* sf2 sf3 */
	"fpu	df4	.64	320	0\n"	/* sf4 sf5 */
	"fpu	df6	.64	328	0\n"	/* sf6 sf7 */
	"fpu	df8	.64	336	0\n"	/* sf8 sf9 */
	"fpu	df10	.64	344	0\n"	/* sf10 sf11 */
	"fpu	df12	.64	352	0\n"	/* sf12 sf13 */
	"fpu	df14	.64	360	0\n"	/* sf14 sf15 */
	"fpu	df16	.64	368	0\n"	/* sf16 sf17 */
	"fpu	df18	.64	376	0\n"	/* sf18 sf19 */
	"fpu	df20	.64	384	0\n"	/* sf20 sf21 */
	"fpu	df22	.64	392	0\n"	/* sf22 sf23 */
	"fpu	df24	.64	400	0\n"	/* sf24 sf25 */
	"fpu	df26	.64	408	0\n"	/* sf26 sf27 */
	"fpu	df28	.64	416	0\n"	/* sf28 sf29 */
	"fpu	df30	.64	424	0\n"	/* sf30 sf31 */
	"fpu	df32	.64	432	0\n"
	"fpu	df34	.64	440	0\n"
	"fpu	df36	.64	448	0\n"
	"fpu	df38	.64	456	0\n"
	"fpu	df40	.64	464	0\n"
	"fpu	df42	.64	472	0\n"
	"fpu	df44	.64	480	0\n"
	"fpu	df46	.64	488	0\n"
	"fpu	df48	.64	496	0\n"
	"fpu	df50	.64	504	0\n"
	"fpu	df52	.64	512	0\n"
	"fpu	df54	.64	520	0\n"
	"fpu	df56	.64	528	0\n"
	"fpu	df58	.64	536	0\n"
	"fpu	df60	.64	544	0\n"
	"fpu	df62	.64	552	0\n"
	"fpu	qf0	.128	304	0\n"	/* sf0 sf1 sf2 sf3 */
	"fpu	qf4	.128	320	0\n"	/* sf4 sf5 sf6 sf7 */
	"fpu	qf8	.128	336	0\n"	/* sf8 sf9 sf10 sf11 */
	"fpu	qf12	.128	352	0\n"	/* sf12 sf13 sf14 sf15 */
	"fpu	qf16	.128	368	0\n"	/* sf16 sf17 sf18 sf19 */
	"fpu	qf20	.128	384	0\n"	/* sf20 sf21 sf22 sf23 */
	"fpu	qf24	.128	400	0\n"	/* sf24 sf25 sf26 sf27 */
	"fpu	qf28	.128	416	0\n"	/* sf28 sf29 sf30 sf31 */
	"fpu	qf32	.128	432	0\n"	/* df32 df34 */
	"fpu	qf36	.128	448	0\n"	/* df36 df38 */
	"fpu	qf40	.128	464	0\n"	/* df40 df42 */
	"fpu	qf44	.128	480	0\n"	/* df44 df46 */
	"fpu	qf48	.128	496	0\n"	/* df48 df50 */
	"fpu	qf52	.128	512	0\n"	/* df52 df54 */
	"fpu	qf56	.128	528	0\n"	/* df56 df68 */
	"fpu	qf60	.128	544	0\n"	/* df60 df62 */
	"gpr	fsr	.64	560	0\n";	/* note that
						   we've left out the filler */
	return r_reg_set_profile_string (anal->reg, p);
}